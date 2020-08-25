#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
//#include <stdio.h>

struct node
{
	char *data;
	struct node* next;
};

int searchNL(char* str, int from);
char *linedup(char *str, unsigned from, unsigned to);

struct node* list_create(char *str)
{
	struct node* n = (struct node*)malloc(sizeof(struct node));
	if(!n) return NULL;
	n->data = str;
	n->next = NULL;
	return n;
}

void list_free(struct node* n)
{
	if(!n) return;
	if(n->next) list_free(n->next);
	free(n->data);
	free(n);
}

int get_next_line(int fd, char **line)
{
	if(fd == -1) return -1;

	static char buffer[BUFFER_SIZE] = {0};
	static int nli = -1;
	int oldnli = nli, lentotal = 0, ret;

	if(nli == -1)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		//printf("buffer: %s\n", buffer);
		if(!ret || ret == -1) { return ret;}
		oldnli = 0;
	}

	//printf("debut nli: %d\n", nli);

	struct node *first, *curr = NULL;

	nli = searchNL(buffer, nli);
	if(nli == -1) curr = list_create(linedup(buffer, oldnli, ret)), lentotal = (ret - oldnli);
	else curr = list_create(linedup(buffer, oldnli, nli)), lentotal = (nli - oldnli);
	first = curr;

	while(!(nli >= 0) && (ret = read(fd, buffer, BUFFER_SIZE)))
	{
		if(ret == -1) { list_free(first); return -1;}
		nli = searchNL(buffer, 0);
		curr->next = list_create(linedup(buffer, 0, nli == -1 ? ret : nli));
		lentotal += (nli ==-1 ? ret : nli);
		curr = curr->next;
	}

	//printf("nli: %d", nli);
	char* result = (char*)malloc(sizeof(char)*(lentotal+1));
	int j = 0, i;

	if(!result) { list_free(first); return -1;}
	for(curr = first; curr; curr = curr->next, j+=i)
	{
		for(i=0; curr->data[i] != '\0'; i++)
			result[j+i] = curr->data[i];
	}

	//printf("fin nli: %d\n", nli);
	result[j] = '\0';
	*line = result;
	list_free(first);
	nli++; if(nli >= ret) nli = -1;
	return 1;
}
