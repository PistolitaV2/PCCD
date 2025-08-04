#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#define HIJOS 3

int cuenta = 0;
int i = 0;
void chld_handler(int senal);

int main(){

	struct sigaction act_chld;
	act_chld.sa_handler = chld_handler;
	act_chld.sa_flags = SA_NODEFER;
	act_chld.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &act_chld, NULL);

	for (i=0; i < HIJOS; i++){
		switch(fork()) {

			case -1: perror("Se ha producido un error en el fork\n");
				return 1;

			case 0: printf("Proceso hijo creado con PID: %i\n", getpid());
				sleep(2+i);
				kill(getpid(),SIGCHLD);
				printf("Proceso hijo con PID %i ha finalizado\n", getpid());
				return 0;
		}
	}
	while(cuenta < 3){
		pause();
	}
	return 0;
}

void chld_handler(int senal){
	cuenta++;
}
