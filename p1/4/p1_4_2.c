#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

	int i,x,y = 0;

	int salida = 0;

	int user_1_recibido = 0, user_2_recibido = 0;



void signal_handler (int senal){

	switch(senal){
		case 10:
			user_1_recibido++;
		break;
		case 12:
			user_2_recibido++;
		break;
		case 15:
			printf("User 1 recibido: %i\n",user_1_recibido);
			printf("User 2 recibido: %i\n",user_2_recibido);
			salida = 1;
		break;
		default:
			printf("Señal no valida");

		break;
	}


}


int main (int argc, char* argv[]){
	
	
	struct sigaction act;

	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESETHAND;

	sigaction(10, &act, NULL);
	sigaction(12, &act, NULL);
	sigaction(15, &act, NULL);

	while (salida == 0) pause();


	return 0;

}