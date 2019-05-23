#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t x;
pthread_mutex_t y;

int xcounter = 0;
int ycounter = 0;

void *A(); 
void *B(); 

int main(int argc, char *argv[])
{
    pthread_t threadA, threadB;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_mutex_init(&x, NULL);
    pthread_mutex_init(&y, NULL);

    pthread_create(&threadA, &attr, A, NULL);
    pthread_create(&threadB, &attr, B, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    pthread_mutex_destroy(&x);
    pthread_mutex_destroy(&y);
    printf("xcounter=%d ycounter=%d\n", xcounter, ycounter);
}

void *A() 
{
    pthread_mutex_lock(&x);
    printf("A lock x\n");
    xcounter ++;
    sleep(1);
    pthread_mutex_lock(&y);
    printf("A lock y\n");
    ycounter ++;
    pthread_mutex_unlock(&y); 
    pthread_mutex_unlock(&x); 

    printf("finished A\n");

    pthread_exit(0);
}

void *B()
{
    pthread_mutex_lock(&x);
    pthread_mutex_lock(&y);
    printf("B lock y\n");
    ycounter --;
    sleep(1);

    printf("B lock x\n");
    xcounter --;
    pthread_mutex_unlock(&x);
    pthread_mutex_unlock(&y);

    pthread_exit(0);
}
