/*
 * 4.
 * Napiste UDP server, který pouzívá pouze 1 proces (1 vlákno) a
 * poskytuje 2 sluzby na 2 portech. Podle toho, na který port prijde pozadavek
 * klienta, se pro jeho zpracování volá funkce zpracuj1 nebo zpracuj2.
 * Funkce zpracuj1 provádí echo, tj. vrátí data klientovi. Funkce zpracuj2 cte
 * a pocítá datagramy tak dlouho, dokud pochází od stejného klienta. Kdyz prijde
 * datagram od jiného klienta, posle puvodnímu klientovi zjistený pocet datagramu
 * a zacne pocítat datagramy od nuly pro nového klienta.
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
#include <sys/socket.h>

#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define PORT1	4000
#define PORT2	5000

#define MAX_C 	10

#define BUF_S	16
int main(int argc, char *argv[])
{
	int sd[2];
	struct sockaddr_in sa[2]; 	

	if ( (sd[0] = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		exit(1);
	sa[0].sin_family = AF_INET;
	sa[0].sin_port = htons(PORT1);
	sa[0].sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sd[0], (struct sockaddr *)&sa[0], sizeof(sa[0])) == -1)
	{
		perror("bind");
		exit(1);
	}
	
		
	if ( (sd[1] = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		exit(1);
	sa[1].sin_family = AF_INET;
	sa[1].sin_port = htons(PORT2);
	sa[1].sin_addr.s_addr = INADDR_ANY;
	
	if( bind(sd[1], (struct sockaddr *)&sa[1], sizeof(sa[1])) == -1)
	{
		perror("bind");
		exit(1);
	}

	int maxfd = sd[0]>sd[1]?sd[0]:sd[1];
	
	fd_set rset;
	
	for(;;)
	{
		FD_ZERO(&rset);
		FD_SET(sd[0], &rset);
		FD_SET(sd[1], &rset);

		if (select(maxfd + 1, &rset, NULL, NULL, NULL) == -1)
		{
			if (errno == EINTR)
				continue;
			else
				exit(1);
		}
		if (FD_ISSET(sd[0],&rset) )
		{
			char buf[BUF_S];
			struct sockaddr_in sin;
			int size_sin = sizeof(sin);
			int rc = recvfrom(sd[0], buf, BUF_S, MSG_DONTWAIT, (struct sockaddr*)&sin, &size_sin);
			fprintf(stderr, "Recv %d\n",rc);
			write(1, buf, rc);

			size_sin = sizeof(sin);
			sendto(sd[0], buf, BUF_S, 0, (struct sockaddr*)&sin,size_sin);
		}
		if (FD_ISSET(sd[1],&rset) )
		{
			char buf[BUF_S];
			struct sockaddr_in sin;
			int size_sin = sizeof(sin);
			int rc = recvfrom(sd[1], buf, BUF_S, 0, (struct sockaddr*)&sin, &size_sin);
			fprintf(stderr, "Recv %d\n",rc);
			write(1, buf, rc);

			size_sin = sizeof(sin);
			sendto(sd[1], buf, BUF_S, 0, (struct sockaddr*)&sin, size_sin);
		}
	}

	exit(0);
}
