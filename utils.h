#include<stdlib.h>
#include<errno.h>

void err_exit(const char *msg) {
  perror(msg);
  exit(errno);
}

void pr_sigmask() {
  sigset_t sig_mask; 

  if (sigprocmask(0, NULL, &sig_mask) < 0) {
    err_exit("get sigmask failed\n");
  } 

  printf("sigmask: ");
  
  if (sigismember(&sig_mask, SIGQUIT)) {
    printf("  SIGQUIT");
  }

  if (sigismember(&sig_mask, SIGINT)) {
    printf("  SIGINT");
  }
  if (sigismember(&sig_mask, SIGALRM)) {
    printf("  SIGALRM");
  }
  if (sigismember(&sig_mask, SIGUSR1)) {
    printf("  SIGUSR1"); 
  }

  printf("\n");
}
