#include <sys/ipc.h>//msgget
#include <sys/types.h>//msgget
#include <sys/msg.h>//msgget
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>//ftok

struct msgbuf{
  long mtype;
  int mtext;
}msg;

int main (int argc, char* argv[]){
    /*int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

       ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
                      int msgflg);
                      If msgtyp is 0, then the first message in the queue is read.


       The msgsnd() and msgrcv() system calls are used, respectively, to send messages to, and receive
       messages from, a System V message queue.  The calling process must have write permission on the
       message queue in order to send a message, and read permission to receive a message.

       The msgp argument is a pointer to a caller-defined structure of the following general form:

           struct msgbuf {
               long mtype;       /* message type, must be > 0
               char mtext[1];    /* message data
           };*/

    int id_cola = 0;
    id_cola = atoi(argv[1]);
    msg.mtype = 1;
    //msg.mtext = 6;
    int longitud = sizeof(msg) - sizeof(long);//restamos el tamaño del mtype
    if(msgrcv(id_cola, &msg, longitud,0, 0) == -1){
      printf("Error al recibir el mensaje\n");
      exit(-1);
    } else {
      printf("Mensaje recibido\n");
    }
    return 0;
}
