#include "./get_next_line/get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;
	int		depth_previous;
	int		depth_current;
	int		total_increases;

	fd = open("./measurements.txt", O_RDONLY);
	str = get_next_line(fd);
	depth_previous = 0;
	total_increases = 0;
	while (str)
	{
		depth_current = atoi(str);
		if (depth_previous && depth_current > depth_previous)
			total_increases++;
		free(str);
		str = get_next_line(fd);
		depth_previous = depth_current;
	}
	printf("total increases = %d\n", total_increases);

}