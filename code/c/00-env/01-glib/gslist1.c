//ex-gslist-1.c
#include <glib.h>
int main(int argc, char** argv) {
 GSList* list = NULL;
 printf("The list is now %d items long\n", g_slist_length(list));
 list = g_slist_append(list, "first");
 list = g_slist_append(list, "second");
 printf("The list is now %d items long\n", g_slist_length(list));
 g_slist_free(list);
 return 0;
}
/*
***** Output *****
 
The list is now 0 items long
The list is now 2 items long
*/