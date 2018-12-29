#define __USE_POSIX

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

#define CHILD_MAX 5

pid_t CH_PIDS[CHILD_MAX] = {}; 


void do_child_user1(int signo){
  printf("%d get signal from %d\n", getpid(), getppid());
}

void do_child(){
  signal(SIGUSR1, do_child_user1);
  while(1){
    sleep(1);
  }
}

void do_user1() {
  printf("%d get signal from %d\n", getpid(), get
}

void do_alarm(int signo){
  for (int i=0; i < CHILD_MAX; i++) {
    kill(CH_PIDS[i], SIGUSR1);
    raise(SIGUSER1);
  }
}


int main(){
  signal(SIGALRM, do_alarm);
  for (int i=0; i < CHILD_MAX; i++) {
    pid_t ch_pid;
    switch ((ch_pid = fork())) {
      case -1:
        perror("fork failed");
        exit(errno);
        break;
      case 0:
        do_child();
        _exit(1);
      default:
        CH_PIDS[i] = ch_pid;    
    }
  } 

  while(1) {
    alarm(1);
    sleep(1);
  }
}
