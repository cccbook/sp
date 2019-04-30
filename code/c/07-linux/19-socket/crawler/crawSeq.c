#include "http.h"
#include "list.c"

int main(int argc, char *argv[]) {
    char head[PACKET_MAX];
    for (int i=0; i<LIST_SIZE; i++) {
        char file[100];
        sprintf(file, "page/misavo_%d.html", i);
        httpDownload("misavo.com", "80", list[i], head, file);
    }
}
