/*
 * Probl�m obedvaj�c�ch filozofu: kolem kulat�ho stolu sed� N filozofu a vzdy
 * mezi dvema filozofy je jedna vidlicka (celkem tedy N vidlicek). Aby se filozof
 * mohl naj�st, potrebuje obe vidlicky, kter� m� u sebe. Nejprve vezme obe
 * vidlicky, pak se naj� a nakonec vidlicky vr�t� na stul. C�lem �lohy je
 * zajistit, aby se kazd� filozof, kdyz dostane hlad, mohl za konecn� cas pustit
 * do j�dla. Je tedy treba zabr�nit deadlocku, napr.: vsichni filozofov� chtej�
 * j�st soucasne, kazd� z nich vezme vidlicku vlevo, ale pak uz z�dn� nem�
 * vidlicku vpravo a vsichni cekaj�.
 *
 * Vyreste probl�m obedvaj�c�ch filozofu s pouzit�m podm�nkov�ch promenn�ch.
 * Kazd� filozof je simulov�n samostatn�m vl�knem. Neblokujte z�dn� vl�kno
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
