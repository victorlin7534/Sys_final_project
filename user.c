#include "bat.h"

int main(int argc, char **argv) {
  int server_socket = client_setup(argv[1]);
  char buffer[BUFFER_SIZE];
  int state;

  
  
  while (1) {
    read(server_socket, buffer, sizeof(buffer));
    if(strcmp(buffer,"SUCCESS")==0){
      state = rand()%;
      write(server_socket,vprintf(),);
    }

    
    int temp = open("temp.c",O_CREAT|O_WRONLY,0644);
     write(temp,buffer,sizeof(buffer));
    execvp("emacs","temp.c");
    close(temp);

    temp = open("temp.c",O_RDWR);
    read(temp,buffer,sizeof(buffer));
    write(server_socket,buffer,sizeof(buffer));
    close(temp);
    remove("temp.c");
  }
}
