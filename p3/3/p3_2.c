#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct{
  int entero;
} zona;

int main(int argc, char* argv[]){
  key_t clave;
  zona *mem_zone;

	clave = ftok("/home/lugilde/Teleco/PCCD/practica/p2", '2');
  //printf("%d\n",clave );
	if(clave == -1){
		printf("Clave no generada.\n");
		return -1;
	}
	int zone = shmget(clave, sizeof(int), IPC_CREAT|0666);
	if(zone == -1){
		printf("No se creado el segmento de memoria.\n");
		return -1;
	}
	printf("Zona de memoria: %d\n", zone);
	mem_zone = shmat(zone, 0, 0);
	if(mem_zone == (-1)){
		printf("Segmento no enlazado.\n");
		return -1;
	} else {
    char caracter;
		while(caracter != 'e'){
			printf("El valor de la zona de memoria es %d.\n", *mem_zone);
			printf("Enter para continuar, 'e' para salir.\n");
			caracter = getchar();
		}
	}
	if(shmdt(mem_zone) == -1){
		printf("Segmento no desenlazado.\n");
	}
	return 0;
}
