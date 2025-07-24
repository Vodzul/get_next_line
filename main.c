
#include "get_next_line.h"
#include <stdio.h>

int	main()
{
	int fd = open("sinan.txt", O_RDWR | O_CREAT, 0777);
	char *line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
