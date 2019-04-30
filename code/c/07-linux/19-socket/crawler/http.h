#ifndef __HTTP_H__
#define __HTTP_H__

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

#define PACKET_MAX 0xfff

void errExit(char *reason);
int httpDownload(char *host, char *port, char *path, char *head, char *file);

#endif