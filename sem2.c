#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMAFORO 0
#define ERROR    -1
#define VECES    10
#define UP        1
#define DOWN     -1

typedef struct sembuf SEMBUF;

int main(int argc, char *argv[]){
   int i = VECES, semid, pid;
   SEMBUF operacion;
   key_t llave;

   /* Petici�n de un identificador con 1 sem�foro */
   llave = ftok(argv[0], 'K');
   if((semid = semget(llave, 1, IPC_CREAT | 0600)) == ERROR){
      perror("semget");
      exit(EXIT_FAILURE);
   }
   /* Inicializaci�n del sem�foro */
   semctl(semid, SEMAFORO, SETVAL, 1);  /* Se inicializa el sem�foro */
   operacion.sem_flg = 0;
   operacion.sem_num = SEMAFORO;

   if((pid = fork()) == ERROR){
      perror("fork");
      exit(EXIT_FAILURE);
   }else if (pid == 0){
      while(i){
         operacion.sem_op = DOWN;   /* Se decrementa el sem�foro */
         semop(semid, &operacion, 1);

         printf("PROCESO HIJO: %d\n", i--);

         operacion.sem_op = UP;   /* Se incrementa el sem�foro */
         semop(semid, &operacion, 1);
      }
      semctl(semid, SEMAFORO, IPC_RMID, NULL); /* Se elimina el sem�foro (aunque el padre ya se encarg� de ello) */
   }else{
      while(i){
         operacion.sem_op = DOWN;   /* Se decrementa el sem�foro */
         semop(semid, &operacion, 1);

         printf("PROCESO PADRE: %d\n", i--);

         operacion.sem_op = UP;   /* Se incrementa el sem�foro */
         semop(semid, &operacion, 1);
      }
      semctl(semid, SEMAFORO, IPC_RMID, NULL); /* Se elimina el sem�foro */
   }
   exit(EXIT_SUCCESS);
}
