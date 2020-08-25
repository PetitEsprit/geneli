#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void test1()
{
	char *line = NULL;
	int fd = open("test", O_RDONLY);
	get_next_line(fd, &line);
	printf("line: %s\n",line);
	if(line) free(line);
	close(fd);
}

int main()
{
	test1();
	return 0;
}
