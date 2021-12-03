#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "../../libft/libft.h"
#include "../../get_next_line/get_next_line.h"

int	main(void)
{
	char	*curr_line;
	int		fd;
	char	**measurement;
	int		distance, depth, aim, buff;

	distance = 0;
	depth = 0;
	aim = 0;
	fd = open("commands.txt", O_RDONLY);
	curr_line = get_next_line(fd);
	while (curr_line)
	{
		measurement = ft_split(curr_line, ' ');
		if (measurement[0][0] == 'f')
		{
			buff = atoi(measurement[1]);
			distance += buff;
			depth += buff * aim;
		}
		else if (measurement[0][0] == 'd')
		{
			aim += atoi(measurement[1]);
		}
		else
		{
			aim -= atoi(measurement[1]);
		}
		ft_free_split(measurement);
		curr_line = get_next_line(fd);
	}
	printf("depth = %d\ndistance = %d\n total = %lu\n", depth, distance, depth * distance);
}