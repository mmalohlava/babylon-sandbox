#include "bigrams.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM 13*25

int compare( const void *arg1, const void *arg2 );

void bigrams(char *s, BIGRAM **big, int *pocet)
{
	int i;
	int len = strlen(s);
	char bg[3];
	
	*pocet = 0;

	*big = (BIGRAM *) malloc(NUM * sizeof(BIGRAM));
	
	for(i=0; i < len-1 ; i++)
	{
		bg[0] = s[i];
		bg[1] = s[i+1];
		bg[2] = '\0';
		for(int j=0; j<*pocet; j++)
		{
			if ( strcmp((*big)[j].bigram, bg) == 0)
			 goto nasel;
		}
		strcpy((*big)[*pocet].bigram, bg);	
		(*big)[*pocet].vyskyt = 0;
		(*pocet)++;
nasel:
		(*big)[j].vyskyt++;
	}

	for(i=0; i<*pocet; i++)
	{
		(*big)[i].fr = (*big)[i].vyskyt/(double)NUM;
	}

	qsort( (void *)(*big), *pocet, sizeof(BIGRAM), compare);
}

int compare( const void *arg1, const void *arg2 )
{
	if ( ((BIGRAM *)arg1)->vyskyt > ((BIGRAM *)arg2)->vyskyt)
		return -1;
	else
	if ( ((BIGRAM *)arg1)->vyskyt == ((BIGRAM *)arg2)->vyskyt)
		return 0;
	else
		return 1;
}

