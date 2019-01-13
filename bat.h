#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#ifndef BAT_H
#define BAT_H

#define BUFFER_SIZE 8192

void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server);


#endif
