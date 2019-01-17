#include "bat.h"

char *question_names[6] = {"base2.c","diff21.c","gcf.c","lastDigit.c","nearHundred.c","sum.c"};

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE], *dummy, pid[50];
  sprintf(pid,"%d",getpid());
  char loc[128]; strcat(loc,"/temp/"); strcat(loc,pid);
  int status;

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

void get_ip(char* addrp){
  struct ifaddrs *iflist,*iface;
  if(getifaddrs(&iflist)<0){
    perror("getifaddrs");
    return;
  }
  for(iface=iflist;iface;iface=iface->ifa_next){
    int af = iface->ifa_addr->sa_family;
    const void *addr;
    if(af == AF_INET) addr = &((struct sockaddr_in *)iface->ifa_addr)->sin_addr;
    else addr = NULL;
    if(addr){
      if(inet_ntop(af,addr,addrp,sizeof(addrp))==NULL){
	perror("inet_ntop");
	continue;
      }
    }
  }
  freeifaddrs(iflist);
}

int main() {
  int listen_socket = server_setup();
  char ip[INET6_ADDRSTRLEN];
  get_ip(ip);
  printf("%s",ip);
  while (1){
    int client_socket = server_connect(listen_socket);
    if (fork()) close(client_socket);
    else subserver(client_socket);
  }
}
