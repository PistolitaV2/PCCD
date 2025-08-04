#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct{
  int quiere_p;
  int quiere_q;
} zona;

int main(int argc, char* argv[]){
  key_t clave;
  zona *mem_zone;
  int numero = atoi(argv[1]);

	clave = ftok("/home/lugilde/Teleco/PCCD/practica/p2", '2');
	if(clave == -1){
		printf("Clave no generada.\n");
		return -1;
	}
	int zone = shmget(clave, sizeof(int), IPC_CREAT|0666);
	if(zone == -1){
		printf("No se creado el segmento de mem_zone.\n");
		return -1;
	}
	printf("Zona de mem_zone: %d\n", zone);
	mem_zone = shmat(zone, NULL, 0);
	if(mem_zone == (-1)){
		printf("Segmento no enlazado.\n");
		return -1;
	} else {
    if(numero==1) mem_zone -> quiere_p = 1;
    else mem_zone -> quiere_q = 1;
		while(1){
      int salida = 1;

			printf("Caminando por mi habitación.\n");
			getchar();
      printf("Dentro del pasillo\n");
      getchar();
      if(numero==1) {
        mem_zone -> quiere_q = 0;
      }else{
        mem_zone -> quiere_p = 0;
     }
      printf("He accionado el pulsador\n");
      getchar();
      while(salida){
			printf("Intentando acceder a la Sección Crítica...\n");,.
			//if((numero == 1 && mem_zone -> quiere_p == 1  && mem_zone -> quiere_q == 0) || (numero == 0 && mem_zone -> quiere_q == 1  && mem_zone -> quiere_p == 0) ){
      if((numero == 1 && mem_zone -> quiere_p == 1  && mem_zone -> quiere_q == 0) || (numero == 0 && mem_zone -> quiere_q == 1  && mem_zone -> quiere_p == 0) ){
        if(numero==1) mem_zone -> quiere_q = 0;
        else mem_zone -> quiere_p = 0;
				printf("Dentro de mi sección crítica\n");
				getchar();
        printf("He salido de mi sección crítica\n");
        getchar();
        if(numero==1) mem_zone -> quiere_q = 1;
        else mem_zone -> quiere_p = 1;
        salida=0;
        printf("He accionado el pulsador\n");
        getchar();
      	continue;
			}else{
				printf("Puerta cerrada\n");
				continue;
			}
    }
		}
  }
	if(shmdt(mem_zone) == -1){
		printf("Segmento no desenlazado.\n");
	}
	return 0;
}
