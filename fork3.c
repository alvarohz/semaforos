#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define VECES 10

int main(){
   int i = 0;

   int status;
   //pid_t pid;
   switch(fork()){
      case -1:
         perror("Error al crear proceso");
         exit(EXIT_FAILURE);
         break;
      case 0: /* Código para el hijo */
         while(i < VECES)
            printf("\t\tProceso HIJO: %d\n", i++);
         break;
      default: /* Código para el padre */
    	 wait (&status); /* espera al final del proceso hijo */
         while(i < VECES)
            printf("\t\tProceso PADRE: %d\n", i++);

		 //return status;
   }
   exit(EXIT_SUCCESS);
}
