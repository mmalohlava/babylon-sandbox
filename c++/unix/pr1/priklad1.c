/*
 * 12.
 * Napiste program pwd, který vypíse cestu od korene k aktuálnímu adresári.
 * Nepouzívejte existující príkaz pwd, funkci getcwd(), nebo jejich ekvivalenty.
 * Nápoveda: jméno odkazu na adresár v jeho rodicovském adresári zjistíte
 * porovnáním císel zarízení a i-uzlu aktuálního adresáre a vsech polozek
 * rodicovského adresáre. Polozka ".." korenového adresáre odkazuje na sebe.
 */
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char * argv[])
{
	DIR *d;
	DIR *last_dir;
	struct dirent *de;
	int dir_fd;
	
	struct stat st_d;
	struct stat st_ld;
	struct stat st;

	char *cesta[1024];
	int pos = 0;
	int i;
	
for(;;)
{
	stat(".", &st_ld);

	if( (d = opendir(".."))==NULL)
	{
		perror("opendir");	
	}
	
	chdir("..");
	while ((de=readdir(d))!=NULL)
	{
		stat(de->d_name, &st);
		if (st.st_dev == st_ld.st_dev && st.st_ino == st_ld.st_ino)
		{ // nasel jsem dir
			cesta[pos] = malloc(strlen(de->d_name)+3);
			strcpy(cesta[pos], de->d_name);
			strcat(cesta[pos], "/");
			pos++;
			fprintf(stderr, "%s/", de->d_name);
			break;
		}
	}
	
	stat("..", &st_d);
	stat(".", &st_ld);
	if ( st_ld.st_dev==st_d.st_dev && st_ld.st_ino==st_d.st_ino )
		break;

	closedir(d);
}
	fprintf(stderr, "\n\n");
	
	fprintf(stderr, "/");
	for(i=pos-1; i>=0; i--)
	{
		fprintf(stderr, "%s", cesta[i]);				
	}
	
	fprintf(stderr, "\n\n");
	exit(0);
}
