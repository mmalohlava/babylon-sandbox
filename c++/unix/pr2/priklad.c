/*
 * 2.
 * Napiste program, který simuluje cinnost shellu pri provádení príkazu
 *
 * ls -lR / 2>&1 | "$PAGER"
 */
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int fd[2];
	int pid1, pid2;
	char *pager;
// fd[0] pro read
// fd[1] pro write
// 
	if ( pipe(fd) == -1)
	{
		perror("pipe()");
		exit(1);
	}

// reader
	switch(pid2 = fork())
	{
		case 0: // child
			close(0);
			dup(fd[0]);	
			close(fd[0]);	
			close(fd[1]);
			execl("/bin/more", "/bin/more", NULL);
			exit(1);
		break;
		case -1: 
			perror("fork()");
			exit(1);
			break;
		default: // father
		break;
	}

// writer
	switch(pid1 = fork())
	{
		case 0: // child
			close(1);
			dup(fd[1]);
			dup2(1,2);
			close(fd[0]);	
			close(fd[1]);
			execl("/bin/ls", "/bin/ls", "/home", "-lR" , NULL);
			exit(1);
		break;
		case -1: 
			perror("fork()");
			exit(1);
			break;
		default: // father
		break;
	}
	close(fd[0]);
	close(fd[1]);

	wait(NULL);
	wait(NULL);
	exit(0);
}
