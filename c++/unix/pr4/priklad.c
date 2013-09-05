/*
 * Pomocí System V IPC semaforu a sdílené pameti implementujte fronty zpráv.
 * Predpokládejte, ze vsechny zprávy ve fronte mají stejnou délku. Zprávy se z
 * fronty vybírají postupne, v poradí, ve kterém byly poslány do fronty.
 * Do fronty muze posílat i z ní prijímat zprávy libovolný pocet procesu.
 * Implementujte operace
 * init(nmesg,sz) - inicializace fronty, nmesg je pocet zpráv, které mohou být
 * soucasne ve fronte, sz je délka zprávy
 * send(msg) - posle zprávu do fronty, pokud uz ve fronte je nmesg zpráv, ceká,
 * az se uvolní místo
 * recv(msg) - precte první zprávu z fronty, kdyz je fronta prázdná, ceká, az
 * prijde zpráva
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

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <errno.h>

key_t smkey = 1234;
key_t skey = 4321;
union semun {
          int val;                  /* value for SETVAL */
          struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
          unsigned short *array;    /* array for GETALL, SETALL */
                                    /* Linux specific part: */
          struct seminfo *__buf;    /* buffer for IPC_INFO */
};
													   
int sem;
int shm_id;
int z;
int k;
int elem_sz;
int q_sz;


void init(int nmesg, int sz)
{

	union semun arg;
	int shm;
	
	elem_sz = sz;
	q_sz    = nmesg;

	if ((shm_id = shmget(smkey, nmesg*sz + 2*sizeof(int), IPC_CREAT|IPC_EXCL|0700)) == -1)
	{
		if (errno == EEXIST)
		{
			if ((shm_id = shmget(smkey, 0, 0)) == -1)
			{
				perror("shmget");
				exit(1);
				
			}
		}
		else
		{
			perror("shmget()");
			exit(1);		
		}
	}

	shm = (int) shmat( shm_id, NULL, 0); 
	*(int *)shm = 0;
	*(int *)(shm+sizeof(int)) = nmesg-1;
	shmdt((void*)shm);
	
	if ((sem = semget(skey, 3, IPC_CREAT|IPC_EXCL|0666) ) == -1)
	{
		if (errno == EEXIST)
			sem = semget(skey, 0, 0);
			else
			{
				perror("semget");
				exit(1);
			}
		
	}

	
	arg.val = sz;
	semctl(sem, 1, SETVAL, arg);
	
	arg.val = 0;
	semctl(sem, 0, SETVAL, arg);
	
	arg.val = 1;
	semctl(sem, 2, SETVAL, arg);

	
}

void send (char a)
{
	int z, k;
	int shm;

	struct sembuf op;
	op.sem_num = 1; // pocet volnych mist 
	op.sem_op  = -1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}
	op.sem_num = 2; // zamek na CV = mutex 
	op.sem_op  = -1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}
	// zapis do sdilene pameti
	shm = shmat( shm_id, NULL, 0); 

	z = *(int *)shm;
	k = *(int *)(shm + sizeof(int));
	
	k = (k+1) % q_sz;
	if (k == z-1)
	{
		exit(1);
	}
	
	*(char *) (shm + elem_sz*k + 2*sizeof(int)) = a;
	*(int *)(shm + sizeof(int)) = k;
	shmdt(shm);
	// end
	
	op.sem_num = 2; // zamek na CV = mutex 
	op.sem_op  = 1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}
	
	op.sem_num = 0; // pocet zapsanych
	op.sem_op  = 1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}
}

char recv()
{
	int z,k;
	struct sembuf op;
	char res = 0;
	int shm;

	op.sem_num = 0; // pocet prvku 
	op.sem_op  = -1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}
	op.sem_num = 2; // zamek na CV = mutex 
	op.sem_op  = -1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}

	// cteni ze sdilene pameti
	
	shm = shmat( shm_id, NULL, 0); 
	z = *(int *)shm;
	k = *(int *)(shm + sizeof(int));
	
	res = *(char *) (shm + elem_sz*z + 2*sizeof(int));
	
	z = (z+1) % q_sz;

	*(int *)(shm )= z;
	shmdt(shm);	
	//end
	//
	op.sem_num = 2; // zamek na CV = mutex 
	op.sem_op  = 1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}
	
	op.sem_num = 2; // pocet volnych 
	op.sem_op  = 1;
	op.sem_flg = 0;
	if ( semop(sem, &op, 1) == -1)
	{
		perror("semop()");
		exit(1);
	}
	return res;
}

int main(int argc, char *argv[])
{
	char rcv;
	init(1024, 1);

	fprintf(stdout, "shmid:%d\nPosilam %c\n", shm_id,'A');
	send('A');

	rcv = recv();
	fprintf(stdout,"Prijimam %c\n", rcv);	

	exit(0);
}
