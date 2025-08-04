#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int salida = 0;

int main (int argc, char* argv[]){
	
	system("clear");
	int pid = atoi(argv[1]);
	char opcion[10] = {};
	while(salida != 1) {
		printf("\nEscoja una opción a realizar con el ascensor\n");
		printf("1.SUBIR\n");
		printf("2.BAJAR\n");
		printf("3.SALIR\n");
		printf("\n");
		fgets(opcion,sizeof(opcion),stdin);
	
		
		if(strlen(opcion) == 2){
			//printf("\nHas seleccionado la opcion %c\n\n",opcion[0]);
		switch(opcion[0]){

			case '1': kill(pid, 10);
				salida = 0;
				break;
			case '2': kill(pid, 12);
				salida = 0;
				break;
			case '3': kill(pid, 3);
				salida = 1;
				break;
			default:
			printf("Has seleccionado una opción no valida\n\n");
		}
	} else {
		printf("\nHas seleccionado una opción no valida\n\n");
	}
}
	return 0;
}