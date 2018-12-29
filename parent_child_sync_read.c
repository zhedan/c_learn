#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include "utils.h"

#define BUF_MAX 2048

static const char *COUNTER_FILE = "/var/log/xc.counter";

void increase_counter() {
  char buf[BUF_MAX];
  
  FILE *fp = fopen(COUNTER_FILE, "r+");
  if (NULL == fgets(buf, sizeof(buf), fp)) {
    err_exit("read counter failed");
  }

  int counter = strtol(buf, NULL, 10);

  counter++;

  fseek(fp, 0, SEEK_SET);
  fprintf(fp, "%d\n", counter);
  fflush(fp);
}

void busy_wait() {
  int i,j;
  volatile int result;
  for (i = 0; i < 100000000; i++) {
    for (j = 0; i< 1000; i++ ) {
      result = i * j;
    }
  }
}

void print_counter() {
  char buf[BUF_MAX];

  FILE *fp = fopen(COUNTER_FILE, "r");

  fgets(buf, sizeof(buf), fp);
  fclose(fp);
  printf("counter is %s\n", buf);
}

void parent_sig_user1(int signo) {
  printf("in parent sig user1\n");
  increase_counter(COUNTER_FILE); 
  print_counter(COUNTER_FILE);
}

void do_parent(pid_t c_pid) {
  while(1) {
    busy_wait();
    kill(c_pid, SIGUSR2);
  }
}

void child_sig_user2(int signo) {
  printf("in child sig user2\n");
  increase_counter(COUNTER_FILE); 
  print_counter(COUNTER_FILE);
}

void do_child() {
  while(1) {
    busy_wait();
    kill(getppid(), SIGUSR1);
  }
}

int main() {
  FILE *fp = fopen(COUNTER_FILE, "w+");

  fputs("0", fp);
  fclose(fp);

  pid_t c_pid;

  signal(SIGUSR1, parent_sig_user1);
  signal(SIGUSR2, child_sig_user2);
  switch (c_pid = fork()) {
    case -1:
      err_exit("fork failed");
      break;

    case 0:
      do_child();
      _Exit(1);

    default:
      do_parent(c_pid);
      _Exit(1);
  }
}
