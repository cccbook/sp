#include "http.h"
#include "list.c"

int main(int argc, char *argv[]) {
    char head[PACKET_MAX];
    httpDownload("example.com", "80", "/", head, "page/example.html");
}
