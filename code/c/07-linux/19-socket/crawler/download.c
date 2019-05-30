#include "http.h"
#include "list.c"

int main(int argc, char *argv[]) {
    char head[PACKET_MAX];
    httpDownload("misavo.com", "80", "/view/ccc/cccForStudent.md", head, "page/cccForStudent.html");
}
