#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
main(void)
{
  void sigusr1_handler(int);
  void sigusr2_handler(int);
  pid_t	child_pid;
  int signal_r=0;
  int signal_code; 
  char pid_str[10];
  if(signal(SIGUSR1, sigusr1_handler)==SIG_ERR){
    perror("SIGQUIT");
    exit(2);
  }
  if(signal(SIGUSR2, sigusr2_handler)==SIG_ERR){
    perror("SIGQUIT");
    exit(2);
  }
  sprintf(pid_str, "%d", getpid());
  if ((child_pid=fork())==0){
    if (execl("signal_child", "signal_child", pid_str, NULL)==-1){
      printf("Error creat procces\n");
      exit(1);
    }
  } else {		
    printf("Forked child %d\n", child_pid);
  }
  sleep(2);
  int i=0;
  while(i<5){
    signal_r = (signal_r + 1) % 2;
    if (signal_r == 0)
      signal_code = SIGUSR1; //SIGUSR1
    else
      signal_code = SIGUSR2; //SIGUSR2
    printf("Parent send %d\n", signal_code);
    if (kill(child_pid, signal_code) ==-1){
      printf("Error seng signal\n");
      exit(1);
    }
    sleep(5);
    i++;
  }
}

void sigusr1_handler(int sgn) {
  printf("Parent get signal SIGUSR1 with code %d\n", sgn);
  signal(sgn, sigusr1_handler);
  sleep(2);
}

void sigusr2_handler(int sgn) {
  printf("Parent get signal SIGUSR2 with code %d\n", sgn);
  signal(sgn, sigusr2_handler);
  sleep(2);
}

