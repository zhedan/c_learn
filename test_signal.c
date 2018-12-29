#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
#include<sys/wait.h>

void err_exit(const char *msg){
  perror(msg);
  exit(errno);
}

void handle_int(int sig) {
  printf("caught SIGINT\n");
  exit(1);
}

void handle_quit(int sig) {
  printf("caught SIGQUIT\n");
  exit(1);
}

void handle_chld(int sig) {
  printf("caught SIGCHLD\n");
  pid_t pid;
  int status;

  do {
    pid = waitpid(-1, &status, WNOHANG);
    if (pid == -1) {
      if (errno == ECHILD) {
        printf("no child to wait\n");
        return;
      }
      else {
        err_exit("waitpid failed in handle_chld");
      }
    } 
    else if (pid == 0){
      printf("handle chld done\n");
      return;
    }
    else {
      printf("child exit, pid: %d\n", pid);
    }
  } while (1);
}

void do_child(){
  printf("do child\n");
  while(1) {
    sleep(1);
  }
}


int main(){
  sig_t old_quit_handler = signal(SIGQUIT, handle_quit);
  sig_t old_chld_handler = signal(SIGCHLD, handle_chld);

  int child_count = 2;
  pid_t pid;

  while (child_count > 0) {
    switch (pid = fork()) {
      case 0:
        do_child();
        _exit(0);
        break;
      case -1:
        err_exit("fork failed");
        break;
      default:
        printf("continue main after fork, child's pid: %d\n", pid);
    }

    child_count--;
  }

  while(1) {
    sleep(1);
  }
}
