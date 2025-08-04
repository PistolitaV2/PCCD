#include <sys/ipc.h>//msgget
#include <sys/types.h>//msgget
#include <sys/msg.h>//msgget
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>//ftok
#include <unistd.h>
#include <errno.h>

struct msgbuf{
  long mtype;
  int tenedor;
} tenedor[6];

void inic_filosofos(int);
void filosofo_comer(int, int);

int main(int argc, char* argv[]){

  int id_cola;
  int opcion;
  int filosofo;
  int borrar_cola;
  key_t key =  ftok("/home/lugilde/Teleco/PCCD/practica",6);


  while(1){
    printf("\nEscoja una opcion:\n");
    printf("1. Introducir tenedores en la cola\n");
    printf("2. Dar de comer a el filosofo\n");
    printf("3. IPCS -Q\n");
    printf("4. Crear cola\n");
    printf("5. Borrar cola\n");
    printf("6. Introducir id_cola\n");
    printf("0. Salir\n");
    scanf("%i",&opcion);
    switch (opcion) {
      case 1: inic_filosofos(id_cola);
      break;

      case 2: printf("\n¿Que filosofo va a comer?\n");
      scanf("%i",&filosofo);
      filosofo_comer(id_cola, filosofo);
      break;

      case 3: printf("\n");
      system("ipcs -q");
      break;

      case 4: if(key == -1){
        printf("Error al generar la key\n");
        exit(-1);
      } else {
        id_cola = msgget(key, IPC_CREAT|0777);
        if(id_cola == -1){
        printf("Error al obtener el identificador de cola \n");
        exit(-1);
        } else {
          printf("\nID cola de mensajes: %i\n",id_cola);
        }
      }
      break;

      case 5: borrar_cola = msgctl(id_cola,IPC_RMID,NULL);
        if(borrar_cola == -1){
          printf("Error al borrar la cola\n");
          exit(-1);
        } else {
          printf("Se ha borrado la cola con el ID_cola: %i\n",id_cola);
        }
        break;

      case 6: printf("\n¿Que cola quiere usar?\n");
      scanf("%i",&id_cola);
      printf("\nSe ha seleccionado la cola con el id_cola: %i\n",id_cola);
      break;

      case 0: exit(0);
      break;
    }
  }
  inic_filosofos(id_cola);
  return 0;
}

void inic_filosofos(int id_cola){
  int i;
  int envio;
  printf("\nIntroduciendo tenedores en la cola %i...\n",id_cola);
  for(i=1;i<6;i++){
    tenedor[i].mtype=i;
    tenedor[i].tenedor=i;
    envio = msgsnd(id_cola, &tenedor[i], sizeof(int), IPC_NOWAIT);
    //perror(&errno);
    if(envio == -1){
      printf("Error en el msgsnd\n");
      exit(-1);
    } else {
      printf("Se ha introducido el tenedor [%i] en la cola.\n",i);
    }
  }
  printf("Se han introducido todos los tenedores en la cola.\n");
}

void filosofo_comer(int id_cola, int filosofo){
  int tenedores;
  printf("El filosofo [%i] intenta coger el tenedor.\n",filosofo);
  msgrcv(id_cola,&tenedor[filosofo], sizeof(int),filosofo,0);
  printf("El filosofo [%i] ha cogido el tenedor [%i].\n",filosofo,filosofo);
  tenedores = filosofo -1;
  if(tenedores == 0) tenedores = 5;
  printf("El filosofo [%i] intenta coger el tenedor.\n",filosofo);
  msgrcv(id_cola,&tenedor[tenedores], sizeof(int),tenedores,0);
  printf("El filosofo [%i] ha cogido el tenedor [%i].\n",filosofo,tenedores);
  printf("El filosofo [%i] esta comiendo.\n",filosofo);
  sleep(5);
  printf("El filosofo [%i] acaba de comer y devuelve los tenedores.\n",filosofo);

	tenedor[tenedores].mtype=tenedores;
	tenedor[tenedores].tenedor=tenedores;
  tenedor[filosofo].mtype=filosofo;
  tenedor[filosofo].tenedor=filosofo;
  msgsnd(id_cola,&tenedor[tenedores], sizeof(int), IPC_NOWAIT);
  msgsnd(id_cola,&tenedor[filosofo], sizeof(int), IPC_NOWAIT);
  }
