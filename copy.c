#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include<sys/wait.h> 

int main(){
    int mypid = getpid();
    char * pidstr = malloc(999);
    sprintf(pidstr, "temp/%d", mypid);
    printf("%s\n",pidstr);
    //if (!fork()){
    //  printf("RM-%d\n",execlp("rm", "-rf", pidstr,(char *)NULL));
    //}
    //execlp("rm", "-rf", pidstr);
    char * pidstrans = malloc(999);
    strcpy(pidstrans,pidstr);
    strcat(pidstrans,"/answers");
    printf("PIDSTRANS:%s\n",pidstrans);
    pid_t child_pid, wpid;
    int status = 0;
    if (!(child_pid =fork())){
      printf("here\n");
      int mkdirtop = execlp("mkdir", "mkdkir","-m","777", pidstr,(char *)NULL);
    }
    while ((wpid = wait(&status)) > 0);
    printf("finished mkdirtop\n");
    if (!(child_pid =fork())){
      printf("here2\n");
      int mkdirans = execlp("mkdir", "mkdkir","-m","777", pidstrans,(char *)NULL);
    }
    while ((wpid = wait(&status)) > 0);
    printf("finished mkdirans\n");
    if (!(child_pid =fork())){
      //printf("here3\n");
      //execlp("pwd","pwd",(char *)NULL);
      int cd = execlp("cp", "cp", "answers/*", pidstr,(char *)NULL);
    }
    while ((wpid = wait(&status)) > 0);
    printf("finished cp\n");
    chdir(pidstr);
    printf("PIDSTR: %s\n",pidstr);
    DIR *d;
    struct dirent *dir;
    d = opendir(pidstr);
    if (d) {
      while ((dir = readdir(d)) != NULL) {
	printf("-------%s\n", dir->d_name);
      }
      closedir(d);
    }


    printf("DONE\n");
    return 0;
}
