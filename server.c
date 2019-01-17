#include "bat.h"

char *question_names[6] = {"base2.c","diff21.c","gcf.c","lastDigit.c","nearHundred.c","sum.c"};

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE], *dummy, pid[50];
  sprintf(pid,"%d",getpid());
  char loc[128]; strcat(loc,"temp/"); strcat(loc,pid);
  int status;

  if(!fork()) execlp("/bin/mkdir","mkdir",loc,NULL);
  else wait(&status);
  
  strcat(loc,"/drivers");
  if(!fork()) execlp("/bin/mkdir","mkdir",loc,NULL);
  else wait(&status);

  while (read(client_socket, buffer, sizeof(buffer))) {
    char q[50];
    strcat(q,"questions/");
    strcat(q,question_names[strtol(buffer,&dummy,10)]);
    
    int temp = open(q,O_RDWR);
    read(temp,buffer,sizeof(buffer));
    write(client_socket, buffer, sizeof(buffer));
    close(temp);

    read(client_socket, buffer, sizeof(buffer));
    strcat(loc,question_names[strtol(buffer,&dummy,10)]);
    temp = open(loc,O_CREAT|O_WRONLY,0644);
    write(temp,buffer,sizeof(buffer));
    close(temp);

    char r[50];
    strcat(r,"answers/");
    char newloc[50]; strcat(newloc,"temp/"); strcat(newloc,pid);
    strcat(r,question_names[strtol(buffer,&dummy,10)]);
    if(!fork()) execlp("/bin/cp","cp",r,newloc,NULL);
    else wait(&status);

    //test
    
    //if(/*success*/) strcpy(buffer,"SUCCESS");
    //else strcpy(buffer,"FAILED");
    remove(loc);

    write(client_socket,buffer,sizeof(buffer));
  }
  close(client_socket);
  if(!fork()) execlp("rm","-rf",strcat("temp/",pid),NULL);
  else wait(&status);
  exit(0);
}

void get_ip(){
  struct ifaddrs *iflist,*iface;
      char addrp[INET6_ADDRSTRLEN];
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
      if(inet_ntop(af,addr,addrp,128)==NULL){
		perror("inet_ntop");
		continue;
      }
    }
  }
  printf("%s\n",addrp);	
  freeifaddrs(iflist);
}

int main() {
  int status;
  if(!fork()) execlp("/bin/mkdir","mkdir","temp",NULL);
  else wait(&status);
  int listen_socket = server_setup();
  get_ip();
  while (1){
    int client_socket = server_connect(listen_socket);
    if (fork()) close(client_socket);
    else subserver(client_socket);
  }
}

// remove temp when exiting
// remove user ip from temp after user exits
// print server ip
// do testing
// delete copy.c
