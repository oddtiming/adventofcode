#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>

char	**fd_to_array(int fd)
{
	char	*curr_line;
	char	**split_array;
	int		i = 0;

	curr_line = get_next_line(fd);
	split_array = malloc(1001 * sizeof(char *));
	while (curr_line)
	{
		split_array[i] = curr_line;
		curr_line = get_next_line(fd);
		i++;
	}
	split_array[i] = NULL;
	return (split_array);
}

char	**update_array(char **split_source, int amount, int index, char most_common_char)
{
	char	**updated_array;
	int		i, j;

	updated_array = malloc((amount + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (split_source[i])
	{
		if (split_source[i][index] == most_common_char)
		{	
			updated_array[j] = ft_strdup(split_source[i]);
			j++;
		}
		i++;
	}
	updated_array[j] = NULL;
	// ft_free_split(split_source);
	return (updated_array);
}

char	get_most_common(char **split_array, int index, int *count)
{
	int	total = 0;

	while (split_array[total])
	{
		if (split_array[total][index] == '1')
			*count+=1;
		total++;
	}
	if (*count * *count> total)
		return ('1');
	else if (*count == (total/2))
		return ('e');
	else
	{
		*count = total - *count;
		return ('0');
	}
}

char	get_least_common(char **split_array, int index, int *count)
{
	int	total = 0;

	while (split_array[total])
	{
		if (split_array[total][index] == '1')
			*count+=1;
		total++;
	}
	if (*count * *count> total)
	{
		printf("count = %d\n", *count);
		*count = total - *count;
		return ('0');
	}
	else if (*count == (total/2))
		return ('e');
	else
		return ('1');
}

char	**get_oxygen_rating(char **split_array)
{
	int		readings_count = 0;
	char	most_common;
	int		index = 0;

	most_common = get_most_common(split_array, index, &readings_count);
	while (readings_count > 1)
	{
		if (most_common == 'e')
			most_common = '1';
		if (readings_count < 10)
		{
			printf("readings_count = %d\n", readings_count);
			for (int i = 0; split_array[i]; i++)
			{
				printf("#%d: %s", i, split_array[i]);
			}
		}
		split_array = update_array(split_array, readings_count, index, most_common);
		index++;
		readings_count = 0;
		get_most_common(split_array, index, &readings_count);
	}
	return (split_array);
}

char	**get_CO2_rating(char **split_array)
{
	int		readings_count = 0;
	char	most_common;
	int		index = 0;

	most_common = get_least_common(split_array, index, &readings_count);
	while (readings_count > 1)
	{
		if (most_common == 'e')
			most_common = '0';
		if (readings_count < 10)
		{
			printf("readings_count = %d\n", readings_count);
			for (int i = 0; split_array[i]; i++)
			{
				printf("#%d: %s", i, split_array[i]);
			}
		}
		split_array = update_array(split_array, readings_count, index, most_common);
		index++;
		readings_count = 0;
		get_least_common(split_array, index, &readings_count);
	}
	return (split_array);
}

int	binary_char_to_int(char *str)
{
	int	int_value = 0;

	for (int i = 0; i < 12; i++)
	{
		if (str[i] == '1')
			int_value |= 0x1;
		if (i != 11)
			int_value <<= 1;
	}
	return (int_value);
}

int main (void)
{
	int		fd;
	char	**split_array;
	int		oxy_rating, CO2_rating;

	oxy_rating = 0;
	CO2_rating = 0;
	fd = open("diagnostic_report.txt", O_RDONLY);
	split_array = fd_to_array(fd);
	split_array = get_oxygen_rating(split_array);
	printf("final oxygen rating = %s\n", split_array[0]);
	oxy_rating = binary_char_to_int(split_array[0]);
	printf("value in decimal = %d\n", oxy_rating);
	ft_free_split(split_array);
	close(fd);

	fd = open("diagnostic_report.txt", O_RDONLY);
	split_array = fd_to_array(fd);
	split_array = get_CO2_rating(split_array);
	printf("final CO2 rating = %s\n", split_array[0]);
	CO2_rating = binary_char_to_int(split_array[0]);
	printf("value in decimal = %d\n", CO2_rating);
	ft_free_split(split_array);
	close(fd);

	printf("total = %d\n", oxy_rating * CO2_rating);
	return (0);
}