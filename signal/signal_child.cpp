#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

main(int argc, char *argv[])
{
  void sigusr1_handler(int);
  void sigusr2_handler(int);
  pid_t parent_pid;
  int signal_r=0;
  int signal_code;  

  if(argc<2){
    printf("Usage 1 args\n");
    exit(1);
  }
  if(signal(SIGUSR1, sigusr1_handler)==SIG_ERR){
    perror("SIGUSR1");
    exit(2);
  }
  if(signal(SIGUSR2, sigusr2_handler)==SIG_ERR){
    perror("SIGUSR2");
    exit(2);
  }
  parent_pid = atoi(argv[1]);
  printf("Parent pid %d\n", parent_pid);

  int i=0;
  while(i<5){ 
    signal_r = (signal_r + 1) % 2;
    if (signal_r == 0)
      signal_code = SIGUSR1; //SIGUSR1
    else
      signal_code = SIGUSR2; //SIGUSR2
    printf("Child send %d\n", signal_code);
    if (kill(parent_pid, signal_code) ==-1){
      printf("Error seng signal\n");
      exit(1);
    }
    sleep(5);
    i++;
  }
}

void sigusr1_handler(int sgn) {
  printf("Child get signal SIGUSR1 with code %d\n", sgn);
  signal(sgn, sigusr1_handler);
  sleep(2);
}

void sigusr2_handler(int sgn) {
  printf("Child get signal SIGUSR2 with code %d\n", sgn);
  signal(sgn, sigusr2_handler);
  sleep(2);
}

