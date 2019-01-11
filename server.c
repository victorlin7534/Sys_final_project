#include "bat.h"

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];
  int state = 0;
  while (read(client_socket, buffer, sizeof(buffer))) {
    
    write(client_socket, buffer, sizeof(buffer));
  }
  close(client_socket);
  exit(0);
}

int main() {
  int listen_socket = server_setup();
  while (1){
    int client_socket = server_connect(listen_socket);
    if (fork()) close(client_socket);
    else subserver(client_socket);
  }
}
