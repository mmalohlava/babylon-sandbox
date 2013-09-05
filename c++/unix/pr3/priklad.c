/*
 *
 * 1.
 * Napiste program, který simuluje cinnost shellu pri interpretaci skriptu
 *
 * /bin/kill -TERM `ps "$1"`
 * echo $?
 * 	
 * 	Pro ctení výstupu vnoreného príkazu pouzijte rouru. Predpokládejte, ze vnorený
 * 	príkaz vypíse pouze jeden rádek, který muze obsahovat více slov (oddelených
 * 	mezerami). Kazdé slovo se predává príkazu kill jako samostatný parametr.
 */

#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int pd[2];
	int pid[2];

	int status;

	if (argc < 2)
	{
		fprintf(stderr, "Pouziti: %s [cislo procesu ke kill]", basename(argv[0]));
		exit(1);
	}
	
	fprintf(stderr, "Process to kill: %s\n", argv[1]);
	
	if ( pipe(pd) == -1 )
	{
		perror("pipe()");
		exit(1);
	}
// writer do roury
	switch(pid[0] = fork())
	{
	case -1:
		perror("fork");
		exit(1);
		break;
	case 0: //child
		if (dup2(pd[1],1) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(pd[0]);
		close(pd[1]);
		execl("/bin/ps", "/bin/ps", "-o","pid","--no-headers",  argv[1], NULL);
		perror("ps");
		fprintf(stderr, "Nepodarilo se spustit ps");
		exit(1);
		break;
	default:
		break;
	}

// reader z roury
	switch(pid[1] = fork())
	{
	case -1:
		perror("fork");
		exit(1);
		break;
	case 0: //child
		if (dup2(pd[0],0) == -1)
		{
			perror("dup2");
			exit(1);
		}

		close(pd[0]);
		close(pd[1]);
		execl("/usr/bin/xargs", "/usr/bin/xargs", "/bin/kill", "-15", NULL);
		perror("xargs");
		fprintf(stderr, "Nepodarilo se spustit xargs");
		exit(1);
		break;
	default:
		break;
	}

	close(pd[0]);
	close(pd[1]);

	waitpid(pid[0], 0, 0);
		
	waitpid(pid[1], &status, 0);
	
	if (WIFEXITED(status))
		fprintf(stderr, "Return code: %d\n", WEXITSTATUS(status));
	exit(0);
}

