#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define HIJOS 3

int cuenta = 0;
int i = 0;
int pid = 0;
int status = 0;

int main(){

	for (i=0; i < HIJOS; i++){
		switch(fork()) {

			case -1: perror("Se ha producido un error en el fork\n");
				return 1;

			case 0: printf("Proceso hijo creado con PID: %i\n", getpid());
				sleep(2+i);
				exit(22);
		}
	}
	for(i=0; i < HIJOS; i++){
		pid = wait(&status);
	//Si el proceso hijo terminó correctamente WIFEXITED(status) retorna un 1.
		if(WIFEXITED(status)){ 
		//Si WIFEXITED(status) es true, devuelve el código de finalización de 8 bits del proceso hijo
		printf("El proceso con PID %i ha finalizado con el código %i\n", pid, WEXITSTATUS(status));
		}
	}
	return 0;
}