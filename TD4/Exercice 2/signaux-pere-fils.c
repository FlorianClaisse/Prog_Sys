#define XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NSIGNORT 32

void handler(int sig) {
  printf("receive: %s\n", strsignal(sig));
}

int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);

  sleep(1); 

  for(int i = 0 ; i < k ; i++) 
    for(int j = 2; j < argc; j++) {
      kill(pere, atoi(argv[j]));
      perror("25 kill: ");
  }

  //sleep(2); 

  kill(pere, 9);
  return 0;
}



int recepteur(int fils, sigset_t *mask, sigset_t *old_mask) {
  printf("récepteur : %d\n", getpid());

  // installation du handler pour tous les signaux non RT
  struct sigaction new, old;
  new.sa_flags = 0;
  sigemptyset(&new.sa_mask);
  perror("43 sigemptyset: ");
  new.sa_handler = handler;

  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    sigaction(sig, &new, &old);
    perror("48 sigaction: ");
  }
  
  sigprocmask(SIG_UNBLOCK, mask, old_mask);
  perror("52 sigprocmask: ");
    
  while(1) 
    pause();
  
  return 0;
}


int main(int argc, char *argv[]) {
  sigset_t mask, old;
  sigemptyset(&mask);
  perror("64 sigemptyset: ");
  for(int sig = 0; sig < NSIGNORT; sig++) {
    sigaddset(&mask, sig);
    perror("65 sigaddset: ");
  }
  sigprocmask(SIG_BLOCK, &mask, &old);
  perror("69 sigprocmask");

  pid_t pid = fork();  
  if (pid == 0) emetteur(getppid(), argc, argv);
  else recepteur(pid, &mask, &old);  
}
