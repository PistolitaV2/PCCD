#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

	int i,x,y = 0;

	int salida = 0;

	int senales_recibidas[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void signal_handler (int senal){

	if (senal == 15){
		salida = 1;
		senales_recibidas [senal-1] = 1;

		for(y=0; y<32; y++) printf("%i",senales_recibidas[y]);
		printf("\n");


	} else {
		senales_recibidas [senal-1] = 1;
	}

}


int main (int argc, char* argv[]){
	
	
	struct sigaction act;

	act.sa_handler = signal_handler;

	for(x=0; x<32; x++) sigaction(x, &act, NULL);

	while (salida == 0) pause();


	return 0;

}

