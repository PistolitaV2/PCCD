#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define T_PISO 3

	int salida = 0;
	int numero_pisos = 0;
	int piso_actual = 0;
	int moviendose = 0;
	int subo = 0;
	int bajo = 0;
	int subiendo = 0;
	int bajando = 0;
	int no_valido = 0;
	void usr1_handler (int senal);
	void usr2_handler (int senal);
	void quit_handler (int senal);
	void alarm_handler (int senal);

int main (int argc, char* argv[]){

	numero_pisos = atoi(argv[1]);
	struct sigaction act_usr1, act_usr2, act_quit, act_alarm;
	act_usr1.sa_handler = usr1_handler;	
	act_usr2.sa_handler = usr2_handler;
	act_quit.sa_handler = quit_handler;	
	act_alarm.sa_handler = alarm_handler;
	printf("Numero de pisos %i\n",numero_pisos);	
	sigaction(10, &act_usr1, NULL);//SIGUSR1
	sigaction(12, &act_usr2, NULL);//SIGUSR2
	sigaction(3, &act_quit, NULL);//SIGQUIT
	sigaction(14, &act_alarm, NULL);//ALARM
	while (salida == 0) {
		if(subiendo == 1){
			subiendo = 0;
			if(piso_actual < numero_pisos){
				piso_actual++;
				subo++;
				alarm(T_PISO);
				moviendose = 1;
				printf("El ascensor está subiendo al piso %i\n",piso_actual);
			} else {
				printf("Ya estás en el piso máximo, no puedes seguir subiendo\n");
			}
		}
		if(bajando == 1){
			bajando = 0;
			if(piso_actual > 0){
				piso_actual--;
				bajo++;
				alarm(T_PISO);
				moviendose = 1;
				printf("El ascensor está bajando al piso %i\n",piso_actual);
			}else {
			printf("Ya estás en el piso mínimo, no puedes seguir bajando\n");
			}
		}
		if (no_valido == 1){
			no_valido = 0;
			printf("Señal no valida");
		}
		if (moviendose == 1){
			printf("Ascensor en movimiento\n");
		} else {
			pause();
		}
	}
	printf("El ascensor ha subido %i pisos\n",subo);
	printf("El ascensor ha bajado %i pisos\n",bajo);
	return 0;
}

void usr1_handler (int senal){
	subiendo = 1;
} 

void usr2_handler (int senal){
	bajando = 1;
} 

void quit_handler (int senal){
	salida = 1;
} 

void alarm_handler (int senal){
	moviendose = 0;
}

