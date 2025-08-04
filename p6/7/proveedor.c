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
} msg[2];



int main(int argc, char* argv[]){
  int id_cola[4];
  int i;
  struct msg[1] mensaje;
  char *ingredientes[]={"fosforos y papel","papel y tabaco", "tabaco y fosforos"};
  int ingredientes_seleccionados;
  key_t key;
  srand(time(NULL));
  for(i=0;i<7;i++){
    key = CLAVES + i;
    id_cola[i] = msgget(key, IPC_CREAT|0777);
    msgctl(id_cola[i], IPC_RMID, NULL);
    id_cola[i] = msgget(key, IPC_CREAT|0777);
  }
  mensaje.mtype=1;
  mensaje.mtext=1;
  msg[2].mtype=5;
  msg[2].mtext=5;
  //msgsnd(id_cola[4],&mensaje,sizeof(int),0);//fosforos
  //msgsnd(id_cola[5],&mensaje,sizeof(int),0);//papel
  //msgsnd(id_cola[6],&mensaje,sizeof(int),0);//tabaco
  while(1){
    ingredientes_seleccionados=rand()%3;
    if(ingredientes_seleccionados==1){
      msgsnd(id_cola[4],&mensaje,sizeof(int),0);//cola fosforos
      msgsnd(id_cola[5],&mensaje,sizeof(int),0);//cola papel
    } else if(ingredientes_seleccionados==2){
      msgsnd(id_cola[5],&mensaje,sizeof(int),0);//cola papel
      msgsnd(id_cola[6],&mensaje,sizeof(int),0);//cola tabaco
    } else {
      msgsnd(id_cola[6],&mensaje,sizeof(int),0);//cola tabaco
      msgsnd(id_cola[4],&mensaje,sizeof(int),0);//cola fosforos
    }
    printf("El proveedor coloca en la mesa los ingredientes: %s\n",ingredientes[ingredientes_seleccionados]);
    msgsnd(id_cola[ingredientes_seleccionados],&mensaje,sizeof(int),0);
    printf("El proveedor esta esperando a que el fumador acabe de fumar\n\n");
    msgrcv(id_cola[3],&mensaje,sizeof(int),(long)1,0);
  }
  exit(0);
}
