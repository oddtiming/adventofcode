#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

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


int	*get_nb_digits(char **split_array, int index)
{
	int	*digits;
	int	jndex = 0;

	digits = malloc(2 * sizeof(int));
	*digits = 0;
	*(digits + 1) = 0;
	while (split_array[jndex])
	{
		if (split_array[jndex][index] == '0')
			*digits += 1;
		else
			*(digits+1) += 1;
		jndex++;
	}
	return (digits);
}


int main (void)
{
	int fd;
	char **split_array;
	int *digits;
	
	fd = open("diagnostic_report.txt", O_RDONLY);
	split_array = fd_to_array(fd);
	digits = get_nb_digits(split_array, 0);
	printf("for index == 0\n# of 0s = %d\n# of 1s = %d\n", *digits, *(digits + 1));
}