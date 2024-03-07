#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *line =  get_next_line(fd);

	while (line)
	{
		printf("%s", line);
		free(line);
		line =  get_next_line(fd);
	}
	free(line);
	system("leaks a.out");
}
