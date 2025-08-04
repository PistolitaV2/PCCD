#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int pid_carvajal,pid_iniesta,pid_ramos,pid_pique,pid_jordi = 0;
int carvajal_listo,jordi_listo, busquets_listo, silva_listo, isco_listo = 0;
int contador = 0;
int i = 0;
int fin_hijo = 0;


int main (int argc, char* argv[]){

    printf("De Gea ");
    //fflush(stdout); // SI NO IMPRIME TODAS LAS VECES DE GEA 

    switch(pid_carvajal=fork()){
        case -1: perror("Error en el fork");
                 exit(-1);

        case 0:  if(execl("p6_hijo", "Carvajal", (char *) NULL) == -1) exit(-1);
                
    }
        
    switch(pid_ramos=fork()){
        case -1: perror("Error en el fork");
                 exit(-1);

        case 0:  if(execl("p6_hijo", "Ramos", (char *) NULL)  == -1) exit(-1);
                 
    }

    switch(pid_pique=fork()){
        case -1: perror("Error en el fork");
                 exit(-1);

        case 0:  if(execl("p6_hijo", "Piqué", (char *) NULL)  == -1) exit(-1);
                 
    }

   // fflush(stdout);
    printf("Jordi-Alba ");
   // fflush(stdout);

    switch(pid_iniesta=fork()){
        case -1: perror("Error en el fork");
                 exit(-1);

        case 0:  if(execl("p6_hijo", "Iniesta Silva", (char *) NULL)  == -1) exit(-1);
                 
    } 
    /*printf("Iniesta ");
    printf("Silva ");
    silva_listo = 1; 
   */
    while(contador != 3){
        fin_hijo=wait(0); 
        if(fin_hijo==pid_iniesta) silva_listo = 1;
        if(fin_hijo==pid_carvajal) carvajal_listo = 1; 
        if(fin_hijo==pid_carvajal || fin_hijo==pid_ramos || fin_hijo==pid_pique) contador++;
        
    }    

        printf("Busquets ");
        printf("Nolito ");
        printf("Isco ");
 
    if(silva_listo != 1) wait(0);

    printf("Aspas\n");

    return 0;
}