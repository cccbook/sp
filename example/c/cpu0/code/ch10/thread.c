#include <pthread.h>
#include <stdio.h>

void *print_george(void *argu) {
  while (1) {
    printf("George\n");
    sleep(1);
  }
  return NULL;
}

void *print_mary(void *argu) {
  while (1) {
    printf("Mary\n");
    sleep(2);
  }
  return NULL;
}

int main() {
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, &print_george, NULL);
  pthread_create(&thread2, NULL, &print_mary, NULL);
  while (1) {
    printf("-------------------------\n");
    sleep(1);
  }
  return 0;
}
