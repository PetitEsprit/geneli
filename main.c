#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void	test1(void)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR fd\n");
		return ;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line: '%s'\n", line);
		free(line);
	}
	close(fd);
}

int	main(void)
{
	test1();
	return (0);
}
