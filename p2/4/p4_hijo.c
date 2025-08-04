#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i = 0;

int main (int argc, char* argv[]){

	for (i=0; i<argc; i++){
		printf("Parámetro %i -> %s\n", i+1, argv[i]);
	}
	sleep(3);
	return 11;
}