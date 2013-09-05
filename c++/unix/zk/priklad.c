/*
 *
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
#include <errno.h>

	int velikost;
	char * prog;

void child(char *adr);

void jdi(char *adr);

void handler(int *);
int main(int argc, char *argv[])
{

	int cnt;
	int pid;
	int i;
	
	if (argc < 4)
	{
		fprintf(stderr, "pouziti \n");
		exit(1);
	}
	
	velikost = atoi(argv[1]);
	prog = argv[2];

	cnt = 3;
	
	
	while (argv[cnt] != NULL)
	{
		switch(pid = fork())
		{
			case -1:
				perror("fork");
				exit(1);
				break;
			case 0:
				child(argv[cnt]);
				break;
			default:
				break;
		}
		cnt++;
	}
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	sigaction(SIGINT, &act, NULL);
		
	for(i=3; i<cnt; i++)
	{
		wait(NULL);
		//pozor na preruseni EINTR!
	}
		
	exit(0);
}

void handler(int *a)
{
	kill(0, SIGTERM);
}
void child(char *adr)
{
	struct sigaction sa;
	sigset_t set;
	jdi(adr);	
	exit(0);
}

void jdi(char *adr)
{
	DIR *d;
	struct dirent *de;
	struct stat st;

	chdir(adr);
	
	if ((d = opendir("."))==NULL)
		perror("opendir");
	while ( (de=readdir(d))!=NULL)
	{
		stat(de->d_name, &st);
		fprintf(stderr, "\n%s", de->d_name);

		if ( (strcmp(de->d_name, ".") == 0) || (strcmp(de->d_name, "..")==0))
		{
			continue;
		}

		if (velikost > st.st_size)
		{
			int pid;
			switch(	pid=fork())
			{
				case -1:
					perror("fork");
					exit(1);
					break;
				case 0:
					execlp(prog, prog, de->d_name,NULL)	;
					fprintf(stderr,"exec()\n");
					exit(1);
				default:
				break;
					
			}
			while ( (wait(NULL)==-1) )
			{
				if (errno == EINTR)
				{
					continue;
				}
				else
				{
					perror("wait");
					exit(1);
				}
			}

		}
			
		if (S_ISDIR(st.st_mode))
		{
			fprintf(stderr, "\tje to dir->rekurze\n");
			if (chdir(de->d_name)==-1)
				perror("chdir()");

			jdi(de->d_name);
		}
	}
	closedir(d);
	chdir("..");
}

