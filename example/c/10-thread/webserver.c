// Multi-Threaded web server using posix pthreads
// BK Turley 2011
// http://kturley.com/simple-multi-threaded-web-server-written-in-c-using-pthreads/
 
//this simple web server is capable of serving simple html, jpg, gif & text files
 
//----- Include files ---------------------------------------------------------
#include <stdio.h>          // for printf()
#include <stdlib.h>         // for exit()
#include <string.h>         // for strcpy(),strerror() and strlen()
#include <fcntl.h>          // for file i/o constants
#include <sys/stat.h>       // for file i/o constants
#include <errno.h>
 
/* FOR BSD UNIX/LINUX  ---------------------------------------------------- */
#include <sys/types.h>      
#include <netinet/in.h>     
#include <sys/socket.h>     /* for socket system calls   */
#include <arpa/inet.h>      /* for socket system calls (bind)  */
#include <sched.h>   
#include "qthread.h"        /* P-thread implementation        */    
#include <signal.h>         /* for signal                     */ 
#include <semaphore.h>      /* for p-thread semaphores        */
/* ------------------------------------------------------------------------ */ 
 
//----- HTTP response messages ----------------------------------------------
#define OK_IMAGE    "HTTP/1.0 200 OK\nContent-Type:image/gif\n\n"
#define OK_TEXT     "HTTP/1.0 200 OK\nContent-Type:text/html\n\n"
#define NOTOK_404   "HTTP/1.0 404 Not Found\nContent-Type:text/html\n\n"
#define MESS_404    "<html><body><h1>FILE NOT FOUND</h1></body></html>"
 
//----- Defines -------------------------------------------------------------
#define BUF_SIZE            1024 /* buffer size in bytes */
#define PORT_NUM            6110 /* Port number for a Web server (TCP 5080) */
#define PEND_CONNECTIONS     100 /* pending connections to hold  */
#define TRUE                   1
#define FALSE                  0
#define NTHREADS 5              /* Number of child threads        */ 
#define NUM_LOOPS  10           /* Number of local loops          */
#define SCHED_INTVL 5           /* thread scheduling interval     */
#define HIGHPRIORITY 10
 
/* global variables ---------------------------------------------------- */
sem_t thread_sem[NTHREADS];  
int   next_thread;  
int   can_run;
int   i_stopped[NTHREADS]; 
 
 
 
/* Child thread implementation ----------------------------------------- */
void *my_thread(void * arg)
{
    unsigned int    myClient_s; /* copy socket */
     
    /* other local variables ------------------------------------------------ */
    char           in_buf[BUF_SIZE];           // Input buffer for GET resquest
    char           out_buf[BUF_SIZE];          // Output buffer for HTML response
    char           *file_name;                 // File name
    unsigned int   fh;                         // File handle (file descriptor)
    unsigned int   buf_len;                    // Buffer length for file reads
    unsigned int   retcode;                    // Return code
    char           *p;
    
    myClient_s = (unsigned int)arg;        // copy the socket
 
    /* receive the first HTTP request (HTTP GET) ------- */
    do {
        printf("waiting for client input\n");
        retcode = recv(myClient_s, in_buf, BUF_SIZE, 0);
        printf("bytes received: %d\n", retcode);
        printf("msg received: %s \n", in_buf);
    } while (retcode == 0);
 
    /* if receive error --- */
    if (retcode < 0) 
        return;
    
    /* if HTTP command successfully received --- */
    else {    
        /* Parse out the filename from the GET request --- */
        strtok_r(in_buf, " ", &p);
        
        file_name = strtok_r(NULL, " ", &p);
        //file_name = "README.md";
        printf("fname: %s \n", &file_name[1]);
        /* Open the requested file (start at 2nd char to get rid */
        /* of leading "\") */
        fh = open(&file_name[1], O_RDONLY, S_IREAD | S_IWRITE);
        //fh = open(file_name, O_RDONLY, S_IREAD | S_IWRITE);
        
        printf("opening file\n");
        /* Generate and send the response (404 if could not open the file) */
        if (fh == -1) {
            printf("File %s not found - sending HTTP 404 \n", &file_name[1]);
            //printf("File %s not found - sending HTTP 404 \n", file_name);
            strcpy(out_buf, NOTOK_404);
            send(myClient_s, out_buf, strlen(out_buf), 0);
            strcpy(out_buf, MESS_404);
            send(myClient_s, out_buf, strlen(out_buf), 0);
        }
        else {
            if ((strstr(file_name, ".jpg") != NULL) ||
                (strstr(file_name, ".gif") != NULL)) {
                strcpy(out_buf, OK_IMAGE);
            }
            else {
                strcpy(out_buf, OK_TEXT);
            }
            printf("sending status\n");
        
            send(myClient_s, out_buf, strlen(out_buf), 0);
 
            buf_len = 1;  
            while (buf_len > 0) {
                buf_len = qthread_read(fh, out_buf, BUF_SIZE);
                /* hack - we'll assume send is non-blocking */
                if (buf_len > 0) 
                    send(myClient_s, out_buf, buf_len, 0);     
            }
 
            close(fh);       // close the file
            close(myClient_s); // close the client connection
            qthread_exit(NULL);
        }
    }
}

//===== Main program ========================================================
int main(int argc, char **argv)
{
    /* local variables for socket connection -------------------------------- */
    unsigned int          server_s;               // Server socket descriptor
    struct sockaddr_in    server_addr;            // Server Internet address
    struct sockaddr_in    client_addr;            // Client Internet address
    struct in_addr        client_ip_addr;         // Client IP address
    int                   addr_len;               // Internet address length
    unsigned int    client_s;       /* Client socket descriptor */
 
    unsigned int          ids;                    // holds thread args
    qthread_attr_t        attr;                   //  qthread attributes
    qthread_t             threads;                // Thread ID (used by OS)
 
    /* create a new socket -------------------------------------------------- */
    server_s = socket(AF_INET, SOCK_STREAM, 0);

    int port_num = 8080;
    if (argc > 1)
        port_num = atoi(argv[1]);
    
    /* fill-in address information, and then bind it ------------------------ */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(server_s, (struct sockaddr *)&server_addr, sizeof(server_addr));
 
    printf("Server at %s\n", inet_ntoa(server_addr.sin_addr));
    /* Listen for connections and then accept ------------------------------- */
    listen(server_s, PEND_CONNECTIONS);
 
    /* the web server main loop ============================================= */
    qthread_attr_init(&attr);
    printf("server ready ...\n");  
    printf("waiting new client ...\n");  
    while(TRUE) {
 
        /* wait for the next client to arrive -------------- */
        addr_len = sizeof(client_addr);
        client_s = qthread_accept(server_s, (struct sockaddr *)&client_addr,
                                  &addr_len);
 
        
        
        if (client_s == FALSE) {
            printf("still false");
            perror("socket");
            //exit(1);
            sleep(1);
            continue;
        }
        else {
            printf("Server got connection from client %s\n", inet_ntoa(client_addr.sin_addr));
            /* Create a child thread --------------------------------------- */
            ids = client_s;
            qthread_create (    /* Create a child thread */
                &threads,       /* Thread ID (system assigned)  */    
                &attr,          /* Default thread attributes    */
                my_thread,      /* Thread routine               */
                (void*)client_s); /* Arguments to be passed       */
         }
    }
 
    close (server_s);           /* close the primary socket */
    return (0);                 /* return code from "main" */
}