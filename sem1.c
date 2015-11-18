#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 75

int main ( )
{
	/* Declaración de variables */
	int semid; 				/* ID de la lista de semáforos */
	struct sembuf sem_oper; /* Para operaciones P y V sobre semáforos */
	union semun {
		int val;
		struct semid_ds *semstat;
		unsigned short *array;
	} arg;

	/* Creamos una lista con dos semáforos */
	semid = semget (SEMKEY, 2, 0777 | IPC_CREAT); //permisos a todo y todos

	/* Inicializamos los semáforos */
	arg.array = (unsigned short *) malloc (sizeof (short)*2);
	arg.array [0] = arg.array [1] = 1;
	semctl (semid, 2, SETALL, arg);

	/* Operamos sobre los semáforos */
	sem_oper.sem_num = 0; 			/* Actuamos sobre el semáforo 0 de la lista */
	sem_oper.sem_op = -1; 			/* Decrementar en 1 el valor del semáforo */
	sem_oper.sem_flg = SEM_UNDO; 	/* Para evitar interbloqueos si un proceso acaba inesperadamente */
	semop (semid, &sem_oper, 1);

	sem_oper.sem_num = 1; 			/* Actuamos sobre el semáforo 1 de la lista */
	sem_oper.sem_op = 1; 			/* Incrementar en 1 el valor del semáforo */
	sem_oper.sem_flg = SEM_UNDO; 	/* No es necesario porque ya se ha hecho anteriormente */
	semop (semid, &sem_oper, 1);

	/* Veamos los valores de los semáforos */
	semctl (semid, 2, GETALL, arg);
	printf ("Los valores de los semaforos son %d y %d", arg.array [0], arg.array [1]);

	/* Eliminar la lista de semáforos */
	semctl (semid, 2, IPC_RMID, 0);
} /* fin de la función main */
