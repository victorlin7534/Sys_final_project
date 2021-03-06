#include "bat.h"

void sighand(int sig){
  if (sig == SIGINT){
    printf("\nWow... giving up already?\n What a disappointment\n");
    if(!fork()) execlp("rm","rm","-rf","temp.c",NULL);
    else wait(0);
    printf("=====Cleaning Up The Mess You Made.=====\n");
    exit(0);
  }
}
int main(int argc, char **argv) {
  signal(SIGINT,sighand);
  char buffer[BUFFER_SIZE], state[2];
  int server_socket, stage = 0;
  if (argc == 2) server_socket = client_setup( argv[1]);
  else server_socket = client_setup( DEFAULT_IP );

  while (stage < 6){  
    sprintf(state,"%d",stage);
    write(server_socket,state,1);
    
    read(server_socket, buffer, sizeof(buffer));

    //put prompt into file for user
    int temp = open("temp.c",O_CREAT|O_WRONLY,0644);
    write(temp,buffer,strlen(buffer));
    if(!fork()) execlp("emacs","emacs","temp.c",NULL);
    else wait(0);
    close(temp);

    memset(buffer,0,sizeof(buffer));

    //send user's work to server
    temp = open("temp.c",O_RDWR);
    read(temp,buffer,sizeof(buffer));
    write(server_socket,buffer,strlen(buffer));
    close(temp);
    remove("temp.c");

    memset(buffer,0,sizeof(buffer));

    //check if user input was correct
    read(server_socket, buffer, 1);
    if(buffer[0]=='5'){printf("SUCCESS\nNEXT TASK\n"); stage++;}
    else printf("FAILED\nDO IT AGAIN!!\n");

    memset(buffer,0,sizeof(buffer));
  }
  printf("You are a master coder now!\n");
}
