#include<stdio.h>
#include<signal.h>
#include "utils.h"

void sig_quit(int signo){
  printf("caught SIGQUIT in normal hanlder\n");
}

void sig_quit_sa_action(int sig_no, siginfo_t *siginfo, void *context) {
  ucontext_t *ucontext = (ucontext_t*)context; 
  printf("caught SIGQUIT in SA_SIGINFO flag\n");
  printf("sender  => uid: %d, pid: %d\n", siginfo->si_uid, siginfo->si_pid);
  printf("sigcode => %d\n", siginfo->si_code); 
}

void sig_chld_sa_action(int sig_no, siginfo_t *siginfo, void *context) {
  ucontext_t *ucontext = (ucontext_t*)context; 
  printf("caught SIGQUIT in SA_SIGINFO flag\n");
  printf("sender  => uid: %d, pid: %d\n", siginfo->si_uid, siginfo->si_pid);
  printf("sigcode => %d\n", siginfo->si_code); 
}

int main() {
  struct sigaction quit_action, oquit_action;
  
  sigemptyset(&quit_action.sa_mask);
  quit_action.sa_handler = sig_quit;
  quit_action.sa_flags = 0;
  
  quit_action.sa_flags |= SA_SIGINFO;
  quit_action.sa_sigaction = sig_quit_sa_action;

  if (sigaction(SIGQUIT, &quit_action, &oquit_action) < 0) {
    err_exit("set SIGQUIT handler failed");
  }

  struct sigaction chld_action, ochld_action;
  sigemptyset(&chld_action.sa_mask);
  chld_action.sa_handler = NULL;
  chld_action.sa_flags |= SA_SIGINFO;
  chld_action.sa_sigaction = sig_chld_sa_action;
 
  if (sigaction(SIGCHLD, &chld_action, &ochld_action)) {
    err_exit("set SIGCHLD handler failed\n");
  }

  while(1) {
    sleep(1);
  }
}
