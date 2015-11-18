#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
	int status;
	if (fork () == 0)
		execl ("/bin/date", "date", 0);
		//first one is the full path, second is process name, ..., argn
	wait (&status);
} /* fin de la función main */
