#include "bat.h"

int main(int argc, char **argv) {
  int server_socket = client_setup(argv[1]);
  char buffer[BUFFER_SIZE];

  int state = rand() % ;
  write(server_socket);//ask server for first prompt

  while (1){
    read(server_socket, buffer, sizeof(buffer));

    //put prompt into file for user
    int temp = open("temp.c",O_CREAT|O_WRONLY,0644);
    write(temp,buffer,sizeof(buffer));
    execvp("emacs","temp.c");
    close(temp);

    //send user's work to server
    temp = open("temp.c",O_RDWR);
    read(temp,buffer,sizeof(buffer));
    write(server_socket,buffer,sizeof(buffer));
    close(temp);
    remove("temp.c");

    read(server_socket, buffer, sizeof(buffer));
    //check if user input was correct
    if(strcmp(buffer,"SUCCESS")==0){
      state = rand()%;
      write(server_socket,,);//send new number/prompt
    }
  }
}
