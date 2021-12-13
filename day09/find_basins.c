#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef	struct s_heightmap
{
	size_t	*map_arr;
	size_t	x_pos;
	size_t	y_pos;
	size_t	x_max;
	size_t	y_max;
	size_t	risk_sum;
}	t_heightmap;

t_heightmap	*init_map_struct(size_t *map_input, size_t x_max, size_t y_max)
{
	t_heightmap	*map;

	map = malloc(sizeof(t_heightmap));
	map->map_arr = map_input;
	map->x_max = x_max;
	map ->y_max = y_max;
	map->risk_sum = 0;
	return (map);
}

void	check_lowest(t_heightmap *map)
{
	//if not beginning of row, check if lower than the one to the left
	if (map->x_pos > 0 && map->map_arr[map->x_pos + (map->y_pos * map->x_max)] >= map->map_arr[map->x_pos - 1 + (map->y_pos * map->x_max)])
		return ;
	//if not end of row, check if lower than the one to the right
	if (map->x_pos < map->x_max - 1 && map->map_arr[map->x_pos + (map->y_pos * map->x_max)] >= map->map_arr[map->x_pos + 1 + (map->y_pos * map->x_max)])
		return ;
	//if not beginning of column, check if lower than the one above
	if (map->y_pos > 0 && map->map_arr[map->x_pos + (map->y_pos * map->x_max)] >= map->map_arr[map->x_pos + ((map->y_pos - 1) * map->x_max)])
		return ;
	//if not end of column, check if lower than the one below
	if (map->y_pos < map->y_max - 1 && map->map_arr[map->x_pos + (map->y_pos * map->x_max)] >= map->map_arr[map->x_pos + ((map->y_pos + 1) * map->x_max)])
		return ;
	//risk level is height + 1
	map->risk_sum += map->map_arr[map->x_pos + (map->y_pos * map->x_max)] + 1;
	printf("lowest at [%lu,%lu] = %lu\n", map->x_pos, map->y_pos, map->map_arr[map->x_pos + map->y_pos * map->x_max] + 1);
	return ;
}

void	solve(t_heightmap *map)
{
	map->y_pos = 0;

	while (map->y_pos < map->y_max)
	{
		map->x_pos = 0;
		while (map->x_pos < map->x_max)
		{
			check_lowest(map);
			// printf("%lu", map->map_arr[map->x_pos + map->y_pos * map->x_max]);
			map->x_pos++;
		}
		// printf("\n");
		map->y_pos++;
	}
	return ;
}

int	main(void)
{
	int		fd;
	size_t	x_max = 0;
	size_t	y_max = 0;
	int 	i;
	int		nb_entries = 0;
	int		total;
	size_t	*map_arr;
	char	read_buff = 0;
	t_heightmap	*map;

	fd = open("input.txt", O_RDONLY);
	while (read(fd, &read_buff, 1))
	{
		if (read_buff == '\n')
		{
			if (!x_max)
				x_max = nb_entries;
			y_max++;
		} 
		else
			nb_entries++;
	}
	//Check if there was new line at end of file
	if (read_buff != '\n')
		y_max++;
	close(fd);

	//Now that we have the amount of inputs, we can parse file into an array
	map_arr = malloc(nb_entries * sizeof(size_t));
	fd = open("input.txt", O_RDONLY);
	i = 0;
	while (read(fd, &read_buff, 1))
	{
		if (read_buff != '\n')
			map_arr[i++] = read_buff - '0';
	}
	close(fd);

	map = init_map_struct(map_arr, x_max, y_max);
	printf("x_max = %lu\ny_max = %lu\n", map->x_max, map->y_max);
	printf("file len = %d\n", nb_entries);
	solve(map);
	printf("\nTotal sum of risk = %lu\n", map->risk_sum);
	free (map->map_arr);
	free (map);
	return (0);
}

/*
	Proceedings:
	- start at lowest point
	
*/