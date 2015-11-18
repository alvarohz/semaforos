#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	pid_t idhijo;
	pid_t idpadre;
	idpadre = getpid(); 	//Se obtiene el id del proceso actual (el padre)
	idhijo = fork(); 		//Se crea un proceso hijo
	if (idhijo == -1) { 	//Si hay un c�digo menor que cero, hubo un error
		perror("Error al realizar la bifurcaci�n"); 	//Se notifica al usuario
		return 1; 			//Se interrumpe la ejecuci�n del proceso con una salida distinta a cero
	}
	if (idhijo == 0) 		//la ejecuci�n de la llamada al sistema fork devuelve un cero al proceso hijo
		printf("Soy el hijo con id %ld id proceso original %ld\n", (long)getpid(), (long)idpadre);
	else 					//la ejecuci�n de la llamada al sistema fork devuelve el identificador al proceso padre
		printf("Soy el padre con id %ld id proceso original %ld\n", (long)getpid(), (long)idpadre);
	return 0;
}
