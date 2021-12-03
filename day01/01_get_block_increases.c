#include "./get_next_line/get_next_line.h"
#include <stdio.h>

int	array_sum(int	*array)
{
	int	total = 0;

	for (int i = 0; i < 3; i++)
		total += array[i];
	return (total);
}

int	main(void)
{
	int		fd;
	char	*str;
	int		array_previous[3];
	int		array_current[3];
	int		atoi_buff;
	int		total_increases;

	fd = open("./measurements.txt", O_RDONLY);
	for (int i = 0; i < 3; i++)
	{
		str = get_next_line(fd);
		atoi_buff = atoi(str);
		array_previous[i] = atoi_buff;
		array_current[i] = atoi_buff;
		free(str);
	}
	total_increases = 0;
	str = get_next_line(fd);
	while (str)
	{
		array_current[0] = array_current[1];
		array_current[1] = array_current[2];
		array_current[2] = atoi(str);
		if (array_sum(array_current) > array_sum(array_previous))
			total_increases++;
		free(str);
		str = get_next_line(fd);
		for (int i = 0; i < 3; i++)
			array_previous[i] = array_current[i];
	}
	printf("total increases = %d\n", total_increases);

}