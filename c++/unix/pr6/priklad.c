/*
 * Problém obedvajících filozofu: kolem kulatého stolu sedí N filozofu a vzdy
 * mezi dvema filozofy je jedna vidlicka (celkem tedy N vidlicek). Aby se filozof
 * mohl najíst, potrebuje obe vidlicky, které má u sebe. Nejprve vezme obe
 * vidlicky, pak se nají a nakonec vidlicky vrátí na stul. Cílem úlohy je
 * zajistit, aby se kazdý filozof, kdyz dostane hlad, mohl za konecný cas pustit
 * do jídla. Je tedy treba zabránit deadlocku, napr.: vsichni filozofové chtejí
 * jíst soucasne, kazdý z nich vezme vidlicku vlevo, ale pak uz zádný nemá
 * vidlicku vpravo a vsichni cekají.
 *
 * Vyreste problém obedvajících filozofu s pouzitím podmínkových promenných.
 * Kazdý filozof je simulován samostatným vláknem. Neblokujte zádné vlákno
 * zbytecne.
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
#include <pthread.h>

#define NUM_FIL	10

char mfork[NUM_FIL];

struct cv_t{
	pthread_mutex_t m;
	pthread_cond_t cv;
};

struct cv_t mcv = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

void * mthread(void *num)
{
	int sec;
	
	int l, r;
	int _i;
	for (_i=0; _i<3; _i++){
	sec = rand() % 3;
	
	sleep(sec);
	r = ((int)num) % NUM_FIL;
	l = ((int)num+1)% NUM_FIL;
	fprintf(stderr, "* Fil %d take %d, %d\n", (int)num,l,r);
	
	pthread_mutex_lock(&mcv.m);
	
	while (mfork[l] == 1 || mfork[r] == 1)
		pthread_cond_wait(&mcv.cv, &mcv.m);
	mfork[l] = mfork[r] = 1;
	
	pthread_mutex_unlock(&mcv.m);
	
	fprintf(stderr, "Fil %d ma obe vidle\n", (int)num);

	pthread_mutex_lock(&mcv.m);
		
	mfork[l] = mfork[r] = 0;
	pthread_cond_broadcast(&mcv.cv);

	pthread_mutex_unlock(&mcv.m);
	}

	pthread_exit(0);	
}

int main(int argc, char *argv[])
{

	pthread_t th[NUM_FIL];

	memset(mfork, 0, NUM_FIL);
	
	int i;
	for(i=0; i<NUM_FIL; i++)
	{
		pthread_create(&th[i], NULL, mthread, (void*)i);
	}
	for(i=0; i<NUM_FIL; i++)
		pthread_join(th[i], NULL);

	exit(0);
}
