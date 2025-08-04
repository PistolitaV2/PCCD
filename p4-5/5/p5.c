#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t semaforo;
sem_t semaforo_escritura[10];
sem_t semaforo_salida[10];
void* thread(int*);

int main(int arg,char* argv[]){
  int N3=atoi(argv[1]);
  pthread_t hilo[N3];
  int error = 0;
  int opcion = 0;
  int escritor = 0;
  int i = 0;
  //If pshared (el segundo argumento) has the value 0, then the semaphore is shared between the threads of a process
  //The value argument(el tercer argumento) specifies the initial value for the semaphore.
  sem_init(&semaforo,0,1);//puede escribir uno a la vez
  for (i = 0; i < N3; i++) {
    error=pthread_create(&hilo[i],NULL,(void*)thread,(void*)i+1);
    if(error!=0){
      printf("No ha sido posible crear el hilo");
      return 0;
    }else{
      sem_init(&semaforo_escritura[i],0,0);
      sem_init(&semaforo_salida[i],0,0);
    }
  }
  while(1){
    printf("\n1.Intentar escribir\n");
    printf("2.Finalizar escribir\n");
    printf("3.Salir\n");
    scanf("%i",&opcion);
    switch(opcion){
      case 1:printf("Introduzca el número del escritor (del 1 al %i)\n",N3);
      scanf("%i",&escritor);
      //sem_post()  increments  (unlocks)  the  semaphore pointed to by sem.  If the semaphore's value consequently becomes greater than zero, then another
      //process or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
      sem_post(&semaforo_escritura[escritor]);
      break;

      case 2:printf("Introduzca el número del escritor (del 1 al %i)\n",N3);
      scanf("%i",&escritor);
      sem_post(&semaforo_salida[escritor]);
      break;

      case 3:return 0;
    }
  }
}

void* thread(int* parametro){
  while(1){
    printf("[escritor %i] -> Esperando a intentar escribir...\n",(int)parametro);
    /*sem_wait() decrements (locks) the semaphore pointed to by sem.  If the semaphore's value is greater than zero, then the decrement proceeds, and the
       function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the
       decrement (i.e., the semaphore value rises above zero), or a signal handler interrupts the call.*/
  	sem_wait(&semaforo_escritura[(int)parametro]);
  	printf("[escritor %i] -> Intentando escribir...\n",(int)parametro);
  	sem_wait(&semaforo);
  	printf("[escritor %i] -> Escribiendo...\n",(int)parametro);
  	sem_wait(&semaforo_salida[(int)parametro]);
  	printf("[escritor %i] -> Fin escritura\n",(int)parametro);
  	sem_post(&semaforo);
  }
  pthread_exit(NULL);
  }
