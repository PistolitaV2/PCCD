#include <sys/ipc.h>//msgget
#include <sys/types.h>//msgget
#include <sys/msg.h>//msgget
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>//ftok

int main (int argc, char* argv[]){

  key_t key =  ftok("/home/lugilde/Teleco/PCCD/practica/p6/1",6);
  if(key == -1){
    printf("Error al generar la key\n");
    exit(-1);
  } else {
    /* The  msgget() system call returns the System V message queue identifier
       associated with the value of the key argument.  A new message queue  is
       created  if  key has the value IPC_PRIVATE or key isn't IPC_PRIVATE, no
       message queue with the given key key exists, and IPC_CREAT is specified
       in msgflg.*/
    int id_cola = msgget(key, IPC_CREAT|0777);
    if(id_cola == -1){
      printf("Error al obtener el identificador de cola \n");
      exit(-1);
    } else {
      printf("ID cola de mensajes: %i\n",id_cola);
    }
  }



}
