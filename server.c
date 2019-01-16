#include "bat.h"

char *question_names[6] = {"base2.c","diff21.c","gcf.c","lastDigit.c","nearHundred.c","sum.c"};

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE], *dummy, pid[50];
  sprintf(pid,"%d",getpid());
  char loc[128]; strcat(loc,"/temp/"); strcat(loc,pid);
  int status;
  
  // print server ip so user can connect to it

  if(!fork()) execlp("mkdir",loc,NULL);
  else wait(&status);
  
  while (read(client_socket, buffer, sizeof(buffer))) {
    char q[50];
    strcat(q,"/questions/");
    strcpy(q,question_names[strtol(buffer,&dummy,10)]);
    
    // copy and remove driver file to be tested from answers to temp folder

    int temp = open(q,O_RDWR);
    read(temp,buffer,sizeof(buffer));
    write(client_socket, buffer, sizeof(buffer));
    close(temp);

    read(client_socket, buffer, sizeof(buffer));
    strcat(loc,q);
    temp = open(loc,O_CREAT|O_WRONLY,0644);
    write(temp,buffer,sizeof(buffer));
    close(temp);

    //test
    
    //if(/*success*/) strcpy(buffer,"SUCCESS");
    //else strcpy(buffer,"FAILED");
    write(client_socket,buffer,sizeof(buffer));
  }
  close(client_socket);
  if(!fork()) execlp("rm","-rf",strcat("/temp/",pid),NULL);
  else wait(&status);
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
