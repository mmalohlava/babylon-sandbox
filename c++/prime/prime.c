#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// find prime numbers up to len
extern void find( char * start_addr, long len );

long fc(long i, char * a)
{
 i += 1;
 a = (char *)0;
 return i;
}


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	 printf("Pouziti:  %s <num>\n\t num = find prime numbers to <num>\n\n",argv[0]);
	 return 0;
	}

	long n = atol(argv[1]);

	long _pom = 2;
	
	while ( n/_pom > 0 )
	{
	 	_pom <<= 1;
	}
	
	long num_bytes = _pom >> 3;
	
	char * bitmap = (char *) malloc( num_bytes * sizeof( char ) );

	if ( !bitmap )
	{
	 printf("Chyba pri alokaci pameti!");
	 return 0;
	}
	
	memset( bitmap, num_bytes, '\0');
	
	printf( "Hledam prvocisla mensi nez %ld:\n" , n);
	printf( "Alokovano %ld bytu pameti.\n", num_bytes);
	
	find( bitmap, num_bytes );
}


