#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>

int	fuel_sum(int pos1, int pos2)
{
	int	i, diff, total;

	diff = abs(pos1 - pos2);
	i = 0;
	total = 0;
	while (i++ < diff)
		total += i;
	return (total);
}

void	print_solution(int *pos_array, size_t nb_entries, int max_value)
{
	int				pos_curr, pos_best, j;
	unsigned long	tot_fuel_best, tot_fuel_curr;

	pos_curr = 0;
	pos_best = 0;
	tot_fuel_best = ULONG_MAX;
	while (pos_curr < max_value)
	{
		j = 0;
		tot_fuel_curr = 0;
		while (j < nb_entries)
		{
			tot_fuel_curr += fuel_sum(pos_curr, pos_array[j]);
			j++;
		}
		if (tot_fuel_curr < tot_fuel_best)
		{
			tot_fuel_best = tot_fuel_curr;
			pos_best = pos_curr;
		}
		pos_curr++;
	}
	printf("best pos = %d\nTotal fuel consumption = %lu\n", pos_best, tot_fuel_best);
}

int	*init_array(size_t nb_entries, char *entries_buff, int *max_value)
{
	int	i, j;
	int	*pos_array;

	pos_array = malloc(nb_entries * sizeof(int));
	i = 0;
	j = 0;
	while (entries_buff[i])
	{
		if (i)
			i++;
		pos_array[j] = atoi(entries_buff + i);
		//to catch the biggest value
		if (pos_array[j] > *max_value)
			*max_value = pos_array[j];
		j++;
		while (isdigit(entries_buff[i]))
			i++;
	}
	return(pos_array);
}

int	main(void)
{
	int		fd, i, read_status, max_value, solution;
	int		*pos_array;
	size_t	nb_entries;
	char	*entries_buff, char_buff;

	i = 0;
	max_value = 0;
	fd = open("input.txt", O_RDONLY);
	entries_buff = malloc(10001);
	read_status = read(fd, entries_buff + i, 10000);
	entries_buff[read_status] = 0;
	//sets at 1, since (# of entries in csv = # of commas + 1)
	nb_entries = 1;
	while (entries_buff[i])
	{
		if (entries_buff[i] == ',')
			nb_entries++;
		i++;
	}
	close(fd);
	// printf("nb entries = %d\nnb_buff: \"%s\"\n", nb_entries, nb_buff);
	pos_array = init_array(nb_entries, entries_buff, &max_value);
	free(entries_buff);
	// for (int j = 0; j < nb_entries; j++)
	// 	printf("array[%d] = %d\n", j, pos_array[j]);
	print_solution(pos_array, nb_entries, max_value);
}