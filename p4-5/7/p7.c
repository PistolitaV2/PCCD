#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem_general,sem_bloq_esc,sem_lectura,sem_escritura,sem_lec[10],sem_lec_sal[10],sem_esc[10],sem_esc_sal[10];
void* thread_lector(int*);
void* thread_escritor(int*);
int N1,N2,N3,K,escritura,lectura = 0;

int main(int argc,char* argv[]){
  N1=atoi(argv[1]);
  N2=atoi(argv[2]);
  N3=atoi(argv[3]);
  K=atoi(argv[4]);
  pthread_t p_lector[N1],p_escritor[N3];
  int i,error,opcion,lector,escritor = 0;
  int idlector[N1],idescritor[N3];

  for (i = 0; i < N1; i++) {
    error=pthread_create(&p_lector[i],NULL,(void*)thread_lector,(void*)i+1);
    if(error!=0){
      printf("No ha sido posible crear el hilo");
      return 0;
    }else{
      sem_init(&sem_lec[i],0,1);
      sem_init(&sem_lec_sal[i],0,1);
      sem_wait(&sem_lec_sal[i]);
      sem_wait(&sem_lec[i]);
    }
  }

  for (i = 0; i < N3; i++) {
    error=pthread_create(&p_escritor[i],NULL,(void*)thread_escritor,(void*)i+1);
    if(error!=0){
      printf("No ha sido posible crear el hilo");
      return 0;
    }else{
      sem_init(&sem_esc[i],0,1);
      sem_init(&sem_esc_sal[i],0,1);
      sem_wait(&sem_esc_sal[i]);
      sem_wait(&sem_esc[i]);
    }
  }

  sem_init(&sem_escritura,0,1);
  sem_init(&sem_lectura,0,N2);
  sem_init(&sem_general,0,1);
  sem_init(&sem_bloq_esc,0,1);


  while(1){
    printf("\n1.Intentar leer");
    printf("\n2.Finalizar leer");
    printf("\n3.Intentar escribir");
    printf("\n4.Finalizar escribir");
    printf("\n0.Salir\n");
    scanf("%i",&opcion);
    switch(opcion){
      case 1:printf("Introduzca el numero del lector (del 1 al %i)\n",N1);
      scanf("%i",&lector);
      //sem_post()  increments  (unlocks)  the  semaphore pointed to by sem.  If the semaphore's value consequently becomes greater than zero, then another
      //process or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
      sem_post(&sem_lec[lector]);
      break;

      case 2:printf("Introduzca el numero del lector (del 1 al %i)\n",N1);
      scanf("%i",&lector);
      sem_post(&sem_lec_sal[lector]);
      break;

      case 3:printf("Introduzca el número del escritor (del 1 al %i)\n",N3);
      scanf("%i",&escritor);
      //sem_post()  increments  (unlocks)  the  semaphore pointed to by sem.  If the semaphore's value consequently becomes greater than zero, then another
      //process or thread blocked in a sem_wait(3) call will be woken up and proceed to lock the semaphore.
      sem_post(&sem_esc[escritor]);
      break;

      case 4:printf("Introduzca el número del escritor (del 1 al %i)\n",N3);
      scanf("%i",&escritor);
      sem_post(&sem_esc_sal[escritor]);
      break;

      case 0:return 0;
    }
  }
  return 0;
}

void* thread_lector(int* parametro){
  while(1){
    printf("\n[Lector %i] -> Esperando a intentar leer...\n",(int)parametro);
    /*sem_wait() decrements (locks) the semaphore pointed to by sem.  If the semaphore's value is greater than zero, then the decrement proceeds, and the
       function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the
       decrement (i.e., the semaphore value rises above zero), or a signal handler interrupts the call.*/
      sem_wait(&sem_lec[(int)parametro]);
  	printf("\n[Lector %i] -> Intentando leer...\n",(int)parametro);
  	sem_wait(&sem_general);
    lectura++;
    if(lectura==1){
      sem_wait(&sem_escritura);
      sem_wait(&sem_bloq_esc);
      if(escritura>K){
        sem_post(&sem_bloq_esc);
        sem_post(&sem_escritura);
        while(escritura>K){
        }
        sem_wait(&sem_escritura);
        sem_wait(&sem_bloq_esc);
      }
      sem_post(&sem_general);
    } else {
      sem_post(&sem_general);
    }
    sem_wait(&sem_lectura);
  	printf("\n[Lector %i] -> Leyendo...\n",(int)parametro);
  	sem_wait(&sem_lec_sal[(int)parametro]);
  	printf("\n[Lector %i] -> Fin lectura\n",(int)parametro);
    sem_post(&sem_lectura);
  	sem_wait(&sem_general);
    lectura--;
    if(lectura==0){
      sem_post(&sem_bloq_esc);
      sem_post(&sem_escritura);
      sem_post(&sem_general);
    } else {
      sem_post(&sem_general);
    }
  }
}


void* thread_escritor(int* parametro){
  while(1){
    printf("\n[Escritor %i] -> Esperando a intentar escribir...\n",(int)parametro);
    /*sem_wait() decrements (locks) the semaphore pointed to by sem.  If the semaphore's value is greater than zero, then the decrement proceeds, and the
       function returns, immediately.  If the semaphore currently has the value zero, then the call blocks until either it becomes possible to perform the
       decrement (i.e., the semaphore value rises above zero), or a signal handler interrupts the call.*/
    sem_wait(&sem_esc[(int)parametro]);
    printf("\n[Escritor %i] -> Intentando escribir...\n",(int)parametro);
    sem_wait(&sem_bloq_esc);
    escritura++;
    sem_post(&sem_bloq_esc);
    sem_wait(&sem_escritura);
    printf("\n[Escritor %i] -> Escribiendo...\n",(int)parametro);
    sem_wait(&sem_esc_sal[(int)parametro]);
    printf("\n[Escritor %i] -> Fin escritura\n",(int)parametro);
    sem_wait(&sem_bloq_esc);
    escritura--;
    sem_post(&sem_bloq_esc);
    sem_post(&sem_escritura);
  }
}
