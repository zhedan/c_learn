#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>
#include<signal.h>
#include "utils.h"

static sigjmp_buf env_buf;
static sig_atomic_t can_jump;

void sig_quit(int signo) {
  printf("caught SIGQUIT\n");
  if (! can_jump) {
    printf("may setjmp not ready\n, just return");
    return;
  } 

  printf("in sig_quit handler\n");
  pr_sigmask();
  alarm(1);
 
  time_t begin_time = time(NULL);
  for( ;; ) {
    time_t cur_time = time(NULL);
    if ( (cur_time - begin_time) > 5) {
      break; 
    }
  }

  can_jump = 0;
  siglongjmp(env_buf, 1);
}

void sig_alarm(int signo) {
  printf("caught SIGALARM\n"); 
  pr_sigmask("in sig_alarm handler\n");
}

int main() {
  signal(SIGQUIT, sig_quit);
  signal(SIGALRM, sig_alarm);
  
  printf("before setjmp\n");
  pr_sigmask();

  if (sigsetjmp(env_buf, 0)) {
    printf("after longjmp\n");
    pr_sigmask();
    exit(0);
  }

  printf("after setjmp\n");
  pr_sigmask();

  can_jump = 1;

  while(1) {
    pause();
  }
}
