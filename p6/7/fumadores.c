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
  const char *ingredientes_poseidos[]={"Fosforos","Tabaco","Papel"};
  const char *ingredientes_necesitados[]={"papel","fosforos", "tabaco"};
  int ingredientes_seleccionados;
  int fumador;
  fumador = atoi(argv[1]);
  key_t key;
  for(i=0;i<7;i++){
    key = CLAVES + i;
    id_cola[i] = msgget(key,IPC_CREAT|0777);
  }
  mensaje.mtype=1;
  mensaje.mtext=1;
  while(1){
    printf("El fumador con [%s] intenta fumar\n",ingredientes_poseidos[fumador]);
    msgrcv(id_cola[fumador],&mensaje,sizeof(int),(long)1,0);
    printf("El fumador con [%s] ha cogido los ingredientes [%s] y esta fumando",ingredientes_poseidos[fumador],ingredientes_necesitados[fumador]);
    getchar();
    printf("El fumador con [%s] ha dejado de fumar\n\n",ingredientes_poseidos[fumador]);
    msgsnd(id_cola[3],&mensaje,sizeof(int),0);
  }
  exit(0);
}
