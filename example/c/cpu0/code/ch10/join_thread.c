#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *print_hello(void *argu)
{
   int i;

   for (i = 0; i < 5; i++) {
      printf("%s,\n", (char *)argu);
      sleep(1);
   }
   return NULL;
}

void *print_world(void *argu)
{
   int i;

   for (i = 0; i < 5; i++) {
      printf("%s!\n", (char *)argu);
      sleep(1);
   }
   return NULL;
}

int main()
{
   pthread_t thread_id1, thread_id2;
   char thread_argu1[256];
   char thread_argu2[256];

   strcpy(thread_argu1, "Hello");
   strcpy(thread_argu2, "World");

   pthread_create(&thread_id1, NULL, &print_hello, thread_argu1);
   pthread_create(&thread_id2, NULL, &print_world, thread_argu2);

   pthread_join(thread_id1, NULL);
   pthread_join(thread_id2, NULL);

   printf("--End of The Program.--\n");

   return 0;
}
