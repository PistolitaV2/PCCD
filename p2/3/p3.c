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
int pid_fork[3] = {};

int main(int argc, char* argv[]){


		switch(pid_fork[i]=fork()) {

			case -1: printf("Se ha producido un error en el fork\n");
				return 1;

			case 0: printf("Proceso hijo creado con PID: %i\n", getpid());
				sleep(15);
				exit(22);
		}
	
	for (i=0; i < HIJOS -1; i++){
		switch(pid_fork[i]=fork()) {

			case -1: printf("Se ha producido un error en el fork\n");
				return 1;

			case 0: printf("Proceso hijo creado con PID: %i\n", getpid());
				sleep(5+i);
				exit(22);
		}
	}
	//for(i=0; i < HIJOS; i++){
		pid = waitpid(pid_fork[1], &status, 0);
		/* wait() and waitpid()
       The wait() system call suspends execution of the calling process  until
       one  of its children terminates.  The call wait(&wstatus) is equivalent
       to:

           waitpid(-1, &wstatus, 0);

       The waitpid() system call suspends execution  of  the  calling  process
       until a child specified by pid argument has changed state.  By default,
       waitpid() waits only for terminated children, but this behavior is mod‐
       ifiable via the options argument, as described below.

       The value of pid can be:

       < -1   meaning  wait  for  any  child process whose process group ID is
              equal to the absolute value of pid.

       -1     meaning wait for any child process.

       0      meaning wait for any child process whose  process  group  ID  is
              equal to that of the calling process.

       > 0    meaning  wait  for  the  child  whose process ID is equal to the
              value of pid.
		*/
		if(WIFEXITED(status)){ 
			//Si el proceso hijo terminó correctamente WIFEXITED(status) retorna un 1.
			//Si WIFEXITED(status) es true, devuelve el código de finalización de 8 bits del proceso hijo
			printf("El proceso con PID %i ha finalizado con el código %i\n", pid, WEXITSTATUS(status));
		}
	//}
	return 0;
}