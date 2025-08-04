#include <sys/ipc.h>//msgget
#include <sys/types.h>//msgget
#include <sys/msg.h>//msgget
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>//ftok

int main (int argc, char* argv[]){
    /* int msgctl(int msqid, int cmd, struct msqid_ds *buf);
       msgctl()  performs  the  control  operation specified by cmd on the System V message queue with
       identifier msqid.*/
    int id_cola = 0;
    id_cola = atoi(argv[1]);
    int borrar_cola = msgctl(id_cola,IPC_RMID,NULL);
    if(borrar_cola == -1){
      printf("Error al borrar la cola\n");
      exit(-1);
    } else {
      printf("Se ha borrado la cola con el ID_cola: %i\n",id_cola);
    }
  }
