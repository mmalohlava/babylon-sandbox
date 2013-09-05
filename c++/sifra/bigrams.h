

typedef struct _BIGRAM
{
	char bigram[3];
	int vyskyt;
	double fr;
} BIGRAM;

void bigrams(char *s, BIGRAM **big, int *pocet);