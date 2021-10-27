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
	line = get_next_line(fd);
	printf("line: '%s'\n",line);
	//line = get_next_line(fd);
	if (line)
		free(line);
	close(fd);
}

int main()
{
	test1();
	return 0;
}
