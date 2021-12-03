#include "get_next_line/get_next_line.h"

int	main(void)
{
	int	array[200];
	int j = 0;

	int fd = open("2020.c", O_RDONLY);
	for (int i = 0; i < 200; i++)
		array[i] = atoi(get_next_line(fd));
	for (int i = 0; i < 200; i++)
	{
		j = i;
		while (j < 200)
		{
			if (array[i] + array[j] == 2020)
				printf("array[%d] (%d) + array[%d] (%d == 2020")
		}
	}
}