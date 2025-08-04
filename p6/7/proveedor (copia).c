#include <sys/ipc.h>//msgget
#include <sys/types.h>//msgget
#include <sys/msg.h>//msgget
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>//ftok
#include <unistd.h>
#include <errno.h>
#define CLAVES 10

struct msgbuf{
  long mtype;
  int mtext;
} msg;



int main(int argc, char* argv[]){
  int id_cola[4];
  int i;
  struct msgbuf mensaje;
  char *ingredientes[]={"papel y tabaco","papel y fosforos", "tabaco y fosforos"};
  int ingredientes_seleccionados;
  key_t key;
  for(i=0;i<4;i++){
    key = CLAVES + i;
    id_cola[i] = msgget(key, IPC_CREAT|0777);
    msgctl(id_cola[i], IPC_RMID, NULL);
    id_cola[i] = msgget(key, IPC_CREAT|0777);
  }
  mensaje.mtype=1;
  mensaje.mtext=1;
  while(1){
    ingredientes_seleccionados=rand()%3;
    printf("El proveedor coloca en la mesa los ingredientes: %s\n",ingredientes[ingredientes_seleccionados]);
    msgsnd(id_cola[ingredientes_seleccionados],&mensaje,sizeof(int),0);
    printf("El proveedor esta esperando a que el fumador acabe de fumar\n\n");
    msgrcv(id_cola[3],&mensaje,sizeof(int),(long)1,0);
  }
  exit(0);
}
