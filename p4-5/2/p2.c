#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


  /* int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

      DESCRIPTION
       The  pthread_create()  function  starts  a  new thread in the calling process.Compile and link with -pthread.*/

typedef struct{
  int posicion;
  char* cadena;
} parametros;

void* thread(parametros * argumentos);

int main(int argc,char* argv[]){
  int error;
  int i;
  pthread_t hilo[argc];
  parametros structParametros[argc-1];
  for(i=0; i<(argc-1);i++){
    structParametros[i].cadena = argv[i+1];
    structParametros[i].posicion = i+1;
    //retorna 0 si todo bien, si algo mal otro numero y el contenido de *thread
    error=pthread_create(&(hilo[i]),NULL,(void*)thread,(void*)&structParametros[i]);
      if(error!=0){
        perror("Error en pthread_create. No se ha creado el hilo.\n");
        exit(-1);
      }else continue;
  }
  //To allow other threads to continue execution, the main thread should terminate by calling pthread_exit() rather than exit(3).
  pthread_exit(NULL);
  return 0;
}

void* thread(parametros * argumentos){
  printf("Posición: %i, Cadena: %s.\n",argumentos->posicion,argumentos->cadena);
  pthread_exit(NULL);
}
