#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* thread_DeGea (void* );
void* thread_Carvajal (void* );
void* thread_Ramos (void* );
void* thread_Pique (void* );
void* thread_JordiAlba (void* );
void* thread_Iniesta (void* );
void* thread_Silva (void* );
void* thread_Busquets (void* );
void* thread_Nolito (void* );
void* thread_Isco (void* );
void* thread_Aspas (void* );


int main(int argc,char* argv[]){

	pthread_t DeGea,Carvajal,Ramos,Pique,JordiAlba,Iniesta,Silva,Busquets,Nolito,Isco,Aspas;
  /*The pthread_join() function waits for the thread specified by thread to
         terminate.  If that thread has already terminated, then  pthread_join()
         returns immediately.  The thread specified by thread must be joinable.*/
	pthread_create(&DeGea, NULL, thread_DeGea, NULL);
  pthread_join(DeGea, NULL);
  pthread_create(&Carvajal, NULL, thread_Carvajal, NULL);
	pthread_create(&Ramos, NULL, thread_Ramos, NULL);
	pthread_create(&Pique, NULL, thread_Pique, NULL);
	pthread_create(&JordiAlba, NULL, thread_JordiAlba, NULL);
  pthread_join(Carvajal, NULL);
	pthread_join(Ramos, NULL);
	pthread_join(Pique, NULL);
  pthread_join(JordiAlba, NULL);
  pthread_create(&Iniesta, NULL, thread_Iniesta, NULL);
  pthread_join(Iniesta, NULL);
  pthread_create(&Silva, NULL, thread_Silva, NULL);
  pthread_join(Silva, NULL);
	pthread_create(&Busquets, NULL, thread_Busquets, NULL);
  pthread_join(Busquets, NULL);
  pthread_create(&Nolito, NULL, thread_Nolito, NULL);
  pthread_join(Busquets, NULL);
  pthread_create(&Isco, NULL, thread_Isco, NULL);
  pthread_join(Isco, NULL);
	pthread_join(Silva, NULL);
	pthread_create(&Aspas, NULL, thread_Aspas, NULL);
  pthread_join(Aspas, NULL);
	pthread_exit(NULL);
	return 0;
}

void* thread_DeGea (void* parametro){
  printf("De Gea ");
  pthread_exit(NULL);
}

void* thread_Carvajal (void* parametro){
  printf("Carvajal ");
  pthread_exit(NULL);
}

void* thread_Ramos (void* parametro){
	printf("Ramos ");
	pthread_exit(NULL);
}

void* thread_Pique (void* parametro){
  printf("Piqué ");
  pthread_exit(NULL);
}

void* thread_JordiAlba (void* parametro){
  printf("Jordi-Alba ");
  pthread_exit(NULL);
}

void* thread_Iniesta (void* parametro){
  printf("Iniesta ");
  pthread_exit(NULL);
}

void* thread_Silva (void* parametro){
  printf("Silva ");
  pthread_exit(NULL);
}

void* thread_Busquets(void* parametro){
  printf("Busquets ");
  pthread_exit(NULL);
}

void* thread_Nolito (void* parametro){
  printf("Nolito ");
  pthread_exit(NULL);
}

void* thread_Isco (void* parametro){
  printf("Isco ");
  pthread_exit(NULL);
}

void* thread_Aspas (void* parametro){
  printf("Aspas ");
  pthread_exit(NULL);
}
