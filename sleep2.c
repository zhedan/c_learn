#include<stdio.h>
#include<setjmp.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>

#define AUTHOR

void sig_int(int signo) {
  printf("handle sig int start\n"); 
  volatile int k;
  for (int i = 0; i < 300000; i++) {
    for (int j = 0; j < 40000; i++) {
      k = i * j; 
    }
  }
  printf("handle sig int finish\n");
}

static jmp_buf env_alarm;

void handle_sleep2_alarm() {
  longjmp(env_alarm, 1); 
}

int sleep2(int sec) {
  signal(SIGALRM, handle_sleep2_alarm); 
  if (setjmp(env_alarm) == 0) {
    alarm(sec);
    pause();
  }
  
  int unslept = 0;
  unslept = alarm(0);
  return unslept;
}

int main() {
  signal(SIGINT, sig_int);

  int unslept = 0;
  unslept = sleep2(5);
  printf("sleep2 return %d\n", unslept);
}
