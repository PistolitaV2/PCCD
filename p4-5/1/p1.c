#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


  /* int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

      DESCRIPTION
       The  pthread_create()  function  starts  a  new thread in the calling process.Compile and link with -pthread.*/

char caracter_teclado;
int contador_caracteres = 0;
void* thread(void*);

int main(int argc,char* argv[]){
  int error;
  pthread_t hilo;
//retorna 0 si todo bien, si algo mal otro numero y el contenido de *thread
  error=pthread_create(&hilo,NULL,thread,NULL);
  if(error!=0){
    perror("Error en pthread_create. No se ha creado el hilo.\n");
    exit(-1);
  }else {
    while(caracter_teclado!='q'){
      sleep(1);
      printf("Número de caracteres leídos del teclado: %i\n",contador_caracteres);
    }
  }
  //To allow other threads to continue execution, the main thread should terminate by calling pthread_exit() rather than exit(3).
  pthread_exit(NULL);
  return 0;
}

void* thread(void* parametro){
  printf("Bienvenido al contador de caracteres. Pulse 'q' para salir.\n");
  while(caracter_teclado!= 'q'){
    caracter_teclado=getchar();
    getchar();//si se tienen que contar los intro como caracteres quitar esto
    contador_caracteres++;

  }
  pthread_exit(NULL);
}
