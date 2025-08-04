#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>


struct msgtype{
  long type;
  int tenedor;
} tenedor[6];

void inic_filosofos(int);
void filosofo_intentar_comer(int,int);

int main(int argc, char* argv[]){
int id_cola;
int filosofo;
int id_tenedor=6;
int key = ftok("/home/PCCD/practica6",3); //creo a cola
if(key == -1){
        printf("Erro na key\n");
        exit(-1);
      } else {
        id_cola = msgget(key, IPC_CREAT|0777);
        if(id_cola == -1){
        printf("Erro creando a cola \n");
        exit(-1);
        } else {
          printf("\nID cola de mensaxes: %i\n",id_cola);
        }
}


inic_filosofos(id_cola);
int seleccion;
while ((1)){
printf("¿Que filosofo vai comer?\n");
scanf("%i",&filosofo);
filosofo_intentar_comer(id_cola,filosofo,id_tenedor);
    /* code */
}


}

void filosofo_intentar_comer(int id_cola, int filosofo){
int id_tenedor=filosofo;
printf("Filosofo %i intenta coller o tenedor\n",filosofo);
msgrcv(id_cola,&tenedor[id_tenedor],sizeof(int),filosofo,0);   
printf("O filosofo %i colleu o tenedor, intentando o outro\n",filosofo); //colle o tenedor que lle corresponde (esquerdo)
id_tenedor=filosofo+1;
if(id_tenedor==6){
    id_tenedor = 0;
printf("O filosofo %i estaba no extremo superior da mesa\n",filosofo);
}
printf("O filosofo %i vai intentar coller o tenedor dereito\n",filosofo); 
msgrcv(id_cola,&tenedor[id_tenedor], sizeof(int),id_tenedor,0);
printf("O filosofo %i colleu o tenedor dereito\nComendo",filosofo); 
int n = 0
for (n=0;n<5;n++){
    sleep(1)
    print(".");
}
printf("O filosofo %i rematou de comer\n",filosofo); 

tenedor[id_tenedor].type=id_tenedor;
tenedor[id_tenedor].tenedor=id_tenedor; //deixo tenedor da dereita
msgsnd(id_cola,&tenedor[id_tenedor],sizeof(int),IPC_NOWAIT);

tenedor[filosofo].type=id_tenedor;
tenedor[filosofo].tenedor=filosofo;     //deixo tenedor da esquerda
msgsnd(id_cola,&tenedor[filosofo],sizeof(int),IPC_NOWAIT);

printf("O filosofo %i deixou os tenedores\n\n",filosofo); 
 
}


void inic_filosofos(int id_cola){

  printf("\nColocando id_tenedor na cola: %i...\n",id_cola);
  int n,erro;
  for(n=1;n<6;n++){
    tenedor[n].type=n;
    tenedor[n].tenedor=n;
    erro = msgsnd(id_cola, &tenedor[n], sizeof(int), IPC_NOWAIT);

    if(envio == -1){
      printf("Erro enviando a mensaxe\n");
      exit(-1);
    } else {
      printf("Colocouse o tenedor [%i] na cola.\n",n);
    }
  }
  printf("id_tenedor listos.\n");
}