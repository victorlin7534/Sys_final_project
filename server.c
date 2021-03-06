#include "bat.h"

char *question_names[6] = {"sum.c","diff21.c","gcf.c","lastDigit.c","nearHundred.c","base2.c"};

void sighand(int sig){
  if (sig == SIGINT){
    printf("\nClosing up shop!\n");
    if (!fork()) execlp("rm","rm","-rf","temp",NULL);
    exit(0);
  }
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE], pid[50];
  sprintf(pid,"%d",getpid());
  char loc[128]; strcat(loc,"temp/"); strcat(loc,pid);

  if(!fork()) execlp("/bin/mkdir","mkdir",loc,NULL);
  else wait(0);
  
  strcat(loc,"/drivers/");
  if(!fork()) execlp("/bin/mkdir","mkdir",loc,NULL);
  else wait(0);

  memset(loc,0,sizeof(loc));
  
  while(read(client_socket, buffer,1)) {
    char question[25];
    strcpy(question,question_names[atoi(buffer)]);
    char q[50] = "questions/";
    strcat(q,question);

    int temp = open(q,O_RDONLY);
    read(temp,buffer,sizeof(buffer));
    write(client_socket, buffer, strlen(buffer));
    close(temp);

    memset(buffer,0,sizeof(buffer));

    strcat(loc,"temp/");strcat(loc,pid);strcat(loc,"/drivers/");strcat(loc,question);
    read(client_socket, buffer, sizeof(buffer));
    temp = open(loc,O_CREAT|O_WRONLY,0644);
    write(temp,buffer,strlen(buffer));
    close(temp);
    memset(loc,0,sizeof(loc));
    
    memset(buffer,0,sizeof(buffer));	   

    char r[50];
    strcat(r,"answers/");
    char newloc[50] = "temp/"; strcat(newloc,pid);
    strcat(r,question);
    if(!fork()) execlp("/bin/cp","cp",r,newloc,NULL);
    else wait(0);
    memset(r,0,sizeof(r));

    chdir(newloc);
    
    if(!fork()) execlp("gcc","gcc",question,NULL);
    else wait(0);
    if(!fork()) execlp("./a.out", "./a.out", NULL);
    else wait(0);

    temp = open("output",O_RDONLY);
    read(temp,buffer,1);
    write(client_socket,buffer,strlen(buffer));
    close(temp);

    memset(buffer,0,sizeof(buffer));

    chdir("../../");
  }
  close(client_socket);
  char path[50] = "temp/";
  strcat(path,pid);
  if(!fork()) execlp("rm","rm","-rf",path,NULL);
  else wait(0);
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
  signal(SIGINT,sighand);
  if(!fork()) execlp("/bin/mkdir","mkdir","temp",NULL);
  else wait(0);
  int listen_socket = server_setup();
  get_ip();
  while (1){
    int client_socket = server_connect(listen_socket);
    if (fork()) close(client_socket);
    else subserver(client_socket);
  }
}
