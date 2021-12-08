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
