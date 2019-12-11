#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<limits.h>
main(int argc, char *argv[])
{
    if(argc<3){
        fprintf(stderr, "Usage %s cmd1 cmd2\n", argv[0]);
        exit(1);
    }
    int fds[argc][2];
    for (int i=0;i<argc-1;i++){
        pipe(fds[i]);
    }
    for (int i=0; i<argc-1;i++){
        if (fork()==0){
            if (i>0) {
                 dup2(fds[i-1][0], 0);
                 close(fds[i-1][1]);
            } else {
                close(fds[i][0]);
            }            
            if (i<argc-2) {
                 dup2(fds[i][1], 1);
            } else {
                close(fds[i][1]);
            }
            for (int u=i+1;u<argc-1;u++){
                close(fds[u][0]);
                close(fds[u][1]);
            }
            execlp(argv[i+1], argv[i+1], NULL);
        } else {
            if (i>0){
                close(fds[i-1][0]);
                close(fds[i-1][1]);
            }
            wait(0);
        }
    }
}
