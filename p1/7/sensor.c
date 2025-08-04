#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int pid_ascensor = 0;
int piso_ascensor = 0;
int salida = 0;
int sensor = 0;
void usr1_handler(int senal);
void chld_handler(int senal);

int main (int argc, char* argv[]){
	
	system("clear");
	piso_ascensor = atoi(argv[1]);
	struct sigaction act_usr1, act_chld;
	act_usr1.sa_handler = usr1_handler;	
	act_chld.sa_handler = chld_handler;	
	act_chld.sa_flags = SA_RESTART;
	sigaction(20, &act_chld, NULL);
	sigaction(10, &act_usr1, NULL);

	printf("Introduzca el PID del ascensor: ");
	scanf("%i", &pid_ascensor);
	while(salida == 0){
		if(sensor ==1){
			sensor = 0;
			sleep(3);
			printf("Se ha activado el sensor del piso %i\n", piso_ascensor);
			kill(pid_ascensor, 14);
		} else {
			pause();
		}
	}
	printf("Sensor desactivado por el pulsador\n");
	return 0;
}

void usr1_handler (int senal){
	salida = 1;
}

void chld_handler (int senal){
	sensor = 1;
}

