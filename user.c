#include "bat.h"


int main(int argc, char **argv) {
  int server_socket;
  if (argc == 2) server_socket = client_setup( argv[1]);
  else server_socket = client_setup( DEFAULT_IP );
  char buffer[BUFFER_SIZE];
  int status;
  int stage = 0;

  char state[8];
  sprintf(state,"%d",stage);
  write(server_socket,state,sizeof(state));//ask server for first prompt

  while (stage < 6){
    read(server_socket, buffer, sizeof(buffer));

    //put prompt into file for user
    int temp = open("temp.c",O_CREAT|O_WRONLY,0644);
    write(temp,buffer,sizeof(buffer));
    if(!fork()) execlp("emacs","temp.c",NULL);
    else wait(&status);
    close(temp);

    //send user's work to server
    temp = open("temp.c",O_RDWR);
    read(temp,buffer,sizeof(buffer));
    write(server_socket,buffer,sizeof(buffer));
    close(temp);
    remove("temp.c");

    read(server_socket, buffer, sizeof(buffer));
    //check if user input was correct
    if(strcmp(buffer,"5")==0){
      stage++;
      sprintf(state,"%d",stage);
      write(server_socket,state,sizeof(state));//send new number/prompt
    }
  }
}
