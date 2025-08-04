#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct{
  int quiere_q;
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
	mem_zone = shmat(zone, NULL, 0);
	if(mem_zone == (-1)){
		printf("Segmento no enlazado.\n");
		return -1;
	} else {
    while(1){
      printf("Caminando por la habitación.\n");
      getchar();
      printf("Intentando entrar en mi sección crítica.\n");
      printf("Dentro de mi sección crítica.\n");
      getchar();
      printf("He salido de mi sección crítica.\n");
    }
	}
	if(shmdt(mem_zone) == -1){
		printf("Segmento no desenlazado.\n");
	}
	return 0;
}
