#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <ctype.h>
#include <strings.h>

void	count_1478(char *line, int **digits_count)
{
	int	i, word_len;

	i = 0;
	word_len = 0;
	while (line[i])
	{
		i = 0;
		while (line[++i] != '|') ;
		while (!isalpha(line[++i])) ;
		while (line[i])
		{
			if (isalpha(line[i]))
				word_len++;
			else
			{
				if (word_len == 2)
					*(*digits_count + 1) += 1;
				else if (word_len == 3)
					*(*digits_count + 7) += 1;
				else if (word_len == 4)
					*(*digits_count + 4) += 1;
				else if (word_len == 7)
					*(*digits_count + 8) += 1;
				word_len = 0;
			}
			i++;
		}
	}
}

int	main(void)
{
	int		fd, i, word_len;
	char	*file_buff;
	int		*digits_count;

	word_len = 0;
	digits_count = malloc(10 * sizeof(int));
	for (i = 0; i < 10; i++)
		digits_count[i] = 0;
	fd = open("input.txt", O_RDONLY);
	file_buff = get_next_line(fd);
	while (file_buff)
	{
		count_1478(file_buff, &digits_count);
		free(file_buff);
		file_buff = get_next_line(fd);
	}
	close(fd);
	printf("# of 1s = %d\n", digits_count[1]);
	printf("# of 4s = %d\n", digits_count[4]);
	printf("# of 7s = %d\n", digits_count[7]);
	printf("# of 8s = %d\n", digits_count[8]);
	printf("sum = %d\n", digits_count[1] + digits_count[4] + digits_count [7] + digits_count[8]);
	return (0);
}

/*
	Todo: build solver
		- create possible outcomes (5 letters = {2, 3, 5} && 6 letters = {0, 6, 9})
		- solve for differences 
		e.g.	if (size(letter_set[i]) == 5 ** 2 elements of letter_set[i] are not part of letter_set[i + 1])
			 		letter_set[i] = 2 || 5);
				if (size(letter_set[i]) == 5 && 1 element of letter_set[i] is not part of letter_set[i + 2])
				{
					letter_set[i] = 2;
					letter_set[i + 2] = 3;
					letter_ser[i + 1] = 5;
					break;
				}
				etc.

*/