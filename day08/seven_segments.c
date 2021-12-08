#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int		fd, i, word_len;
	char	*file_buff;
	int		digits_count[10] = { 0 };

	word_len = 0;
	fd = open("input.txt", O_RDONLY);
	file_buff = get_next_line(fd);
	while (file_buff)
	{
		i = 0;
		while (file_buff[i])
		{
			for (i = 0; file_buff[i] && file_buff[i] != '|'; i++) ;
			while (!isalpha(file_buff[i]))
				i++;
			while (file_buff[i])
			{
				if (isalpha(file_buff[i]))
					word_len++;
				else
				{
					if (word_len == 2)
						digits_count[1]++;
					else if (word_len == 3)
						digits_count[7]++;
					else if (word_len == 4)
						digits_count[4]++;
					else if (word_len == 7)
						digits_count[8]++;
					word_len = 0;
				}
				i++;
			}
		}
		free(file_buff);
		file_buff = get_next_line(fd);
	}
	close(fd);
	printf("# of 1s = %d\n", digits_count[1]);
	printf("# of 4s = %d\n", digits_count[4]);
	printf("# of 7s = %d\n", digits_count[7]);
	printf("# of 8s = %d\n", digits_count[8]);
	printf("sum = %d\n", digits_count[1] + digits_count[4] + digits_count [7] + digits_count[8]);
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