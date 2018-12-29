#include<stdio.h>
#include<stdlib.h>
#include<signal.h>


void sig_quit(int signo) {
  printf("caught SIGQUIT\n");

  if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
    perror("restore SIGQUIT handler to SIG_DFL faild\n");
  }
  printf("SIGQUIT has restored to SIG_DFL\n");
}

int main() {
  sigset_t nset, oset, pending_sigs;
  
  if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
    perror("set SIGQUIT handler failed\n");
    exit(1);
  }

  sigemptyset(&nset);
  sigaddset(&nset, SIGQUIT);
  if (sigprocmask(SIG_BLOCK, &nset, &oset) < 0) {
    perror("set sigprocmas failed");
    exit(1);
  }
  sleep(5);

  sigpending(&pending_sigs);

  if (sigismember(&pending_sigs, SIGQUIT)) {
    printf("SIGQUIT pending\n"); 
  }

  if (sigprocmask(SIG_SETMASK, &oset, NULL) < 0) {
    perror("restore sigmask failed\n");
    exit(1);
  }
  printf("SIGQUIT is restored\n");

  sleep(5);
  return 0;
}
