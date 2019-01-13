#include "bat.h"

void error_check( int i, char *s ) {
  if ( i < 0 ) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
    exit(1);
  }
}

int server_setup() {
  int sd = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( sd, "server socket" );
  printf("[server] socket created\n");

  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET; 
  hints->ai_socktype = SOCK_STREAM; 
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, PORT, hints, &results); 

  int i = bind( sd, results->ai_addr, results->ai_addrlen );
  error_check( i, "server bind" );
  printf("[server] socket bound\n");

  i = listen(sd, 10);
  error_check( i, "server listen" );
  printf("[server] socket in listen state\n");

  free(hints);
  freeaddrinfo(results);
  return sd;
}

int server_connect(int sd) {
  struct sockaddr_storage client_address;
  socklen_t sock_size = sizeof(client_address);
  int client_socket = accept(sd, (struct sockaddr *)&client_address, &sock_size);
  error_check(client_socket, "server accept");

  struct sockadd_in *sin = (struct sockaddr_in*)&client_address;
  char *ip = inet_ntoa(sin.sin_addr);
  char loc[128] = strcat("/temp/",ip);
  excvp("mkdir","loc");
  
  return client_socket;
}

int client_setup(char * server) {
  int sd = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( sd, "client socket" );

  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  
  hints->ai_socktype = SOCK_STREAM;  
  getaddrinfo(server, PORT, hints, &results);

  int i = connect( sd, results->ai_addr, results->ai_addrlen );
  error_check( i, "client connect" );

  free(hints);
  freeaddrinfo(results);

  return sd;
}
