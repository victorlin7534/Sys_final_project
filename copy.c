#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(){
    int mypid = getpid();
    char * pidstr = malloc(999);
    sprintf(pidstr, "temp/%d", mypid);
    printf("%s",pidstr);
    printf("RM-%d\n",execlp("rm", "-rf", pidstr));
    printf("MKDIR-%d\n",execlp("mkdir", "mkdkir", pidstr));
    char * extpid = malloc(999);
    strcpy(extpid, pidstr);
    strcat(extpid, "/*");
    printf("CP-%d\n",execlp("cp", "cp", "-R", extpid));
    chdir(pidstr);


    DIR *d;
    struct dirent *dir;
    d = opendir("temp");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("-------%s\n", dir->d_name);
        }
        closedir(d);
    }


    printf("DONE\n");
}