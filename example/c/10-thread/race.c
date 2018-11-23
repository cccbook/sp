#include <stdio.h>
#include <pthread.h>

#define LOOPS 100000000
int counter = 0;

void *inc()
{
  for (int i=0; i<LOOPS; i++) {
    counter = counter + 1;
  }
  return NULL;
}

void *dec()
{
  for (int i=0; i<LOOPS; i++) {
    counter = counter - 1;
  }
  return NULL;
}


int main() 
{
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, inc, NULL);
  pthread_create(&thread2, NULL, dec, NULL);

  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  printf("counter=%d\n", counter);
}
