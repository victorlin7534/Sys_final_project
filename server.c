#include "bat.h"

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];
  while (read(client_socket, buffer, sizeof(buffer))) {
  	char *q = question_names[];

    int temp = open(strcat("/questions/",q),O_RDWR);
    read(temp,buffer,sizeof(buffer));
    write(client_socket, buffer, sizeof(buffer));
    close(temp);

    read(client_socket, buffer, sizeof(buffer));
    char *loc = strcat("/temp/",q);//get user to tell server its ip
    temp = open(loc,O_CREAT|O_WRONLY,0644);
    write(temp,buffer,sizeof(buffer));
    close(temp);

    //testing

    if(/*success*/) buffer = "SUCCESS";
    else buffer = "FAILED";
    write(client_socket,buffer,sizeof(buffer));
    remove(loc);
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
