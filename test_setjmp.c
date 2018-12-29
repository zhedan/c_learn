#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>
#include<signal.h>
#include "utils.h"

static jmp_buf env_buf;
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
  sleep(5);

  longjmp(env_buf, 1);
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

  if (setjmp(env_buf)) {
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
