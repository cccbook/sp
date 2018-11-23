#include <sys/socket.h>       // socket definitions
#include <sys/types.h>        // socket types
#include <arpa/inet.h>        // inet (3) funtions
#include <unistd.h>           // misc. UNIX functions
#include <signal.h>           // signal handling
#include <stdlib.h>           // standard library
#include <stdio.h>            // input/output library
#include <string.h>           // string library
#include <errno.h>            // error number library
#include <fcntl.h>            // for O_* constants
#include <sys/mman.h>         // mmap library
#include <sys/types.h>        // various type definitions
#include <sys/stat.h>         // more 
#include <pthread.h>

// global constants
#define PORT 2001             // port to connect on
#define LISTENQ 10            // number of connections

int list_s;                   // listening socket

// structure to hold the return code and the filepath to serve to client.
typedef struct {
	int returncode;
	char *filename;
} httpRequest;

// Structure to hold variables that will be placed in shared memory
typedef struct {
	pthread_mutex_t mutexlock;
	int totalbytes;
} sharedVariables;

// headers to send to clients
char *header200 = "HTTP/1.0 200 OK\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n";
char *header400 = "HTTP/1.0 400 Bad Request\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n";
char *header404 = "HTTP/1.0 404 Not Found\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n";

// get a message from the socket until a blank line is recieved
char *getMessage(int fd) {
  
    // A file stream
    FILE *sstream;
    
    // Try to open the socket to the file stream and handle any failures
    if( (sstream = fdopen(fd, "r")) == NULL)
    {
        fprintf(stderr, "Error opening file descriptor in getMessage()\n");
        exit(EXIT_FAILURE);
    }
    
    // Size variable for passing to getline
    size_t size = 1;
    
    char *block;
    
    // Allocate some memory for block and check it went ok
    if( (block = malloc(sizeof(char) * size)) == NULL )
    {
        fprintf(stderr, "Error allocating memory to block in getMessage\n");
        exit(EXIT_FAILURE);
    }
  
    // Set block to null    
    *block = '\0';
    
    // Allocate some memory for tmp and check it went ok
    char *tmp;
    if( (tmp = malloc(sizeof(char) * size)) == NULL )
    {
        fprintf(stderr, "Error allocating memory to tmp in getMessage\n");
        exit(EXIT_FAILURE);
    }
    // Set tmp to null
    *tmp = '\0';
    
    // Int to keep track of what getline returns
    int end;
    // Int to help use resize block
    int oldsize = 1;
    
    // While getline is still getting data
    while( (end = getline( &tmp, &size, sstream)) > 0)
    {
        // If the line its read is a caridge return and a new line were at the end of the header so break
        if( strcmp(tmp, "\r\n") == 0)
        {
            break;
        }
        
        // Resize block
        block = realloc(block, size+oldsize);
        // Set the value of oldsize to the current size of block
        oldsize += size;
        // Append the latest line we got to block
        strcat(block, tmp);
    }
    
    // Free tmp a we no longer need it
    free(tmp);
    
    // Return the header
    return block;

}

// send a message to a socket file descripter
int sendMessage(int fd, char *msg) {
    return write(fd, msg, strlen(msg));
}

// Extracts the filename needed from a GET request and adds public_html to the front of it
char * getFileName(char* msg)
{
    // Variable to store the filename in
    char * file;
    // Allocate some memory for the filename and check it went OK
    if( (file = malloc(sizeof(char) * strlen(msg))) == NULL)
    {
        fprintf(stderr, "Error allocating memory to file in getFileName()\n");
        exit(EXIT_FAILURE);
    }
    
    // Get the filename from the header
    sscanf(msg, "GET %s HTTP/1.1", file);
    
    // Allocate some memory not in read only space to store "public_html"
    char *base;
    if( (base = malloc(sizeof(char) * (strlen(file) + 18))) == NULL)
    {
        fprintf(stderr, "Error allocating memory to base in getFileName()\n");
        exit(EXIT_FAILURE);
    }
    
    char* ph = "public_html";
    
    // Copy public_html to the non read only memory
    strcpy(base, ph);
    
    // Append the filename after public_html
    strcat(base, file);
    
    // Free file as we now have the file name in base
    free(file);
    
    // Return public_html/filetheywant.html
    return base;
}

// parse a HTTP request and return an object with return code and filename
httpRequest parseRequest(char *msg){
    httpRequest ret;
       
    // A variable to store the name of the file they want
    char* filename;
    // Allocate some memory to filename and check it goes OK
    if( (filename = malloc(sizeof(char) * strlen(msg))) == NULL)
    {
        fprintf(stderr, "Error allocating memory to filename in parseRequest()\n");
        exit(EXIT_FAILURE);
    }
    // Find out what page they want
    filename = getFileName(msg);
    
    // Check if its a directory traversal attack
    char *badstring = "..";
    char *test = strstr(filename, badstring);
    
    // Check if they asked for / and give them index.html
    int test2 = strcmp(filename, "public_html/");
    
    // Check if the page they want exists 
    FILE *exists = fopen(filename, "r" );
    
    // If the badstring is found in the filename
    if( test != NULL )
    {
        // Return a 400 header and 400.html
        ret.returncode = 400;
        ret.filename = "400.html";
    }
    
    // If they asked for / return index.html
    else if(test2 == 0)
    {
        ret.returncode = 200;
        ret.filename = "public_html/index.html";
    }
    
    // If they asked for a specific page and it exists because we opened it sucessfully return it 
    else if( exists != NULL )
    {
        
        ret.returncode = 200;
        ret.filename = filename;
        // Close the file stream
        fclose(exists);
    }
    
    // If we get here the file they want doesn't exist so return a 404
    else
    {
        ret.returncode = 404;
        ret.filename = "404.html";
    }
    
    // Return the structure containing the details
    return ret;
}

// print a file out to a socket file descriptor
int printFile(int fd, char *filename) {
  
    /* Open the file filename and echo the contents from it to the file descriptor fd */
    
    // Attempt to open the file 
    FILE *read;
    if( (read = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Error opening file in printFile()\n");
        exit(EXIT_FAILURE);
    }
    
    // Get the size of this file for printing out later on
    int totalsize;
    struct stat st;
    stat(filename, &st);
    totalsize = st.st_size;
    
    // Variable for getline to write the size of the line its currently printing to
    size_t size = 1;
    
    // Get some space to store each line of the file in temporarily 
    char *temp;
    if(  (temp = malloc(sizeof(char) * size)) == NULL )
    {
        fprintf(stderr, "Error allocating memory to temp in printFile()\n");
        exit(EXIT_FAILURE);
    }
    
    
    // Int to keep track of what getline returns
    int end;
    
    // While getline is still getting data
    while( (end = getline( &temp, &size, read)) > 0)
    {
        sendMessage(fd, temp);
    }
    
    // Final new line
    sendMessage(fd, "\n");
    
    // Free temp as we no longer need it
    free(temp);
    
    // Return how big the file we sent out was
    return totalsize;
  
}

// clean up listening socket on ctrl-c
void cleanup(int sig) {
    
    printf("Cleaning up connections and exiting.\n");
    
    // try to close the listening socket
    if (close(list_s) < 0) {
        fprintf(stderr, "Error calling close()\n");
        exit(EXIT_FAILURE);
    }
    
    // Close the shared memory we used
    shm_unlink("/sharedmem");
    
    // exit with success
    exit(EXIT_SUCCESS);
}

int printHeader(int fd, int returncode)
{
    // Print the header based on the return code
    switch (returncode)
    {
        case 200:
        sendMessage(fd, header200);
        return strlen(header200);
        break;
        
        case 400:
        sendMessage(fd, header400);
        return strlen(header400);
        break;
        
        case 404:
        sendMessage(fd, header404);
        return strlen(header404);
        break;
    }
    return -1;
}


// Increment the global count of data sent out 
int recordTotalBytes(int bytes_sent, sharedVariables *mempointer)
{
    // Lock the mutex
    pthread_mutex_lock(&(*mempointer).mutexlock);
    // Increment bytes_sent
    (*mempointer).totalbytes += bytes_sent;
    // Unlock the mutex
    pthread_mutex_unlock(&(*mempointer).mutexlock);
    // Return the new byte count
    return (*mempointer).totalbytes;
}


int main(int argc, char *argv[]) {
    printf("Web Server run at localhost:2001\n");
    printf("Start http://localhost:2001/index.html\n");
    
    int conn_s;                  //  connection socket
    short int port = PORT;       //  port number
    struct sockaddr_in servaddr; //  socket address structure
    
    // set up signal handler for ctrl-c
    (void) signal(SIGINT, cleanup);
    
    // create the listening socket
    if ((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        fprintf(stderr, "Error creating listening socket.\n");
        exit(EXIT_FAILURE);
    }
    
    // set all bytes in socket address structure to zero, and fill in the relevant data members
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(port);
    
    // bind to the socket address
    if (bind(list_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
        fprintf(stderr, "Error calling bind()\n");
        exit(EXIT_FAILURE);
    }
    
    
    // Listen on socket list_s
    if( (listen(list_s, 10)) == -1)
    {
        fprintf(stderr, "Error Listening\n");
        exit(EXIT_FAILURE);
    } 
    
    // Set up some shared memory to store our shared variables in
    
    // Close the shared memory we use just to be safe
    shm_unlink("/sharedmem");
    
    int sharedmem;
    
    // Open the memory
    if( (sharedmem = shm_open("/sharedmem", O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) == -1)
    {
        fprintf(stderr, "Error opening sharedmem in main() errno is: %s ", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    // Set the size of the shared memory to the size of my structure
    ftruncate(sharedmem, sizeof(sharedVariables) );
    
    // Map the shared memory into our address space
    sharedVariables *mempointer;
    
    // Set mempointer to point at the shared memory
    mempointer = mmap(NULL, sizeof(sharedVariables), PROT_READ | PROT_WRITE, MAP_SHARED, sharedmem, 0); 
    
    // Check the memory allocation went OK
    if( mempointer == MAP_FAILED )
    {
        fprintf(stderr, "Error setting shared memory for sharedVariables in recordTotalBytes() error is %d \n ", errno);
        exit(EXIT_FAILURE);
    }
    // Initalise the mutex
    pthread_mutex_init(&(*mempointer).mutexlock, NULL);
    // Set total bytes sent to 0
    (*mempointer).totalbytes = 0;

    // Size of the address
    socklen_t addr_size = sizeof(servaddr);
    
    // Sizes of data were sending out
    int headersize;
    int pagesize;
    int totaldata;
    // Number of child processes we have spawned
    int children = 0;
    // Variable to store the ID of the process we get when we spawn
    pid_t pid;
    
    // Loop infinitly serving requests
    while(1)
    {
    
        // If we haven't already spawned 10 children fork
        if( children <= 10)
        {
            pid = fork();
            children++;
        }
        
        // If the pid is -1 the fork failed so handle that
        if( pid == -1)
        {
            fprintf(stderr,"can't fork, error %d\n" , errno);
            exit (1);
        }
        
        // Have the child process deal with the connection
        if ( pid == 0)
        {	
            // Have the child loop infinetly dealing with a connection then getting the next one in the queue
            while(1)
            {
                // Accept a connection
                conn_s = accept(list_s, (struct sockaddr *)&servaddr, &addr_size);
                    
                // If something went wrong with accepting the connection deal with it
                if(conn_s == -1)
                {
                    fprintf(stderr,"Error accepting connection \n");
                    exit (1);
                }
                
                // Get the message from the file descriptor
                char * header = getMessage(conn_s);
                
                // Parse the request
                httpRequest details = parseRequest(header);
                
                // Free header now were done with it
                free(header);
                
                // Print out the correct header
                headersize = printHeader(conn_s, details.returncode);
                
                // Print out the file they wanted
                pagesize = printFile(conn_s, details.filename);
                
                // Increment our count of total datasent by all processes and get back the new total
                totaldata = recordTotalBytes(headersize+pagesize, mempointer);
                
                // Print out which process handled the request and how much data was sent
                printf("Process %d served a request of %d bytes. Total bytes sent %d  \n", getpid(), headersize+pagesize, totaldata);	
                
                // Close the connection now were done
                close(conn_s);
            }
        }
    }
    return EXIT_SUCCESS;
}
