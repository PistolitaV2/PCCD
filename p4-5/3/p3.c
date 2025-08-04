#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* thread_Carvajal (void* );
void* thread_Ramos (void* );
void* thread_Pique (void* );
void* thread_IniestaSilva (void* );


int main(int argc,char* argv[]){

	pthread_t Carvajal,Ramos,Pique,IniestaSilva;

	printf("De Gea ");
  pthread_create(&Carvajal, NULL, thread_Carvajal, NULL);
	pthread_create(&Ramos, NULL, thread_Ramos, NULL);
	pthread_create(&Pique, NULL, thread_Pique, NULL);
	printf("Jordi-Alba ");
  pthread_create(&IniestaSilva, NULL, thread_IniestaSilva, NULL);
  /*The pthread_join() function waits for the thread specified by thread to
         terminate.  If that thread has already terminated, then  pthread_join()
         returns immediately.  The thread specified by thread must be joinable.*/
	pthread_join(Carvajal, NULL);
	pthread_join(Ramos, NULL);
	pthread_join(Pique, NULL);
	printf("Busquets ");
	printf("Nolito ");
	printf("Isco ");
	pthread_join(IniestaSilva, NULL);
	printf("Aspas\n");
	pthread_exit(NULL);
	return 0;
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

void* thread_IniestaSilva (void* parametro){
  printf("Iniesta ");
	printf("Silva ");
  pthread_exit(NULL);
}
