#include <stdlib.h>

char *linedup(char *str, unsigned from, unsigned to)
{
	unsigned i, j=0;
	int size = to-from + 1;
	if(size < 0) return NULL;
	char *res = (char*)malloc(sizeof(char)*size);
	if(!res) return NULL;

	for(i=from ; i<to; i++,j++)
		res[j]=str[i];
	res[j] = '\0';
	return res;
}

int searchNL(char* str, int from)
{
	int i = (from == -1? 0 : from);
	for( ; str[i] != '\n' && str[i] != '\0'; i++);
	if(str[i] == '\n') return i;
	return -1;
}
