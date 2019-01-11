#include "bat.h"

int main(int argc, char **argv) {
  int server_socket = client_setup(argv[1]);
  char buffer[BUFFER_SIZE];

  while (1) {
    read(server_socket, buffer, sizeof(buffer));
    
    
    int temp = open("temp.c",O_CREAT|O_WRONLY,0644);
    write(temp,buffer,sizeof(buffer));
    execvp("emacs","temp.c");
    close(temp);

    char check[BUFFER_SIZE];
    temp = open("temp.c",O_RDONLY);
    read(temp,check,sizeof(check));
    write(server_socket,check,sizeof(check));
    close(temp);
    remove("temp.c");
  }
}
