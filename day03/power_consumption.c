#include "../../get_next_line/get_next_line.h"
#include "../../libft/libft.h"
#include <stdio.h>


int main (void)
{
	int fd;
	char *curr_line;
	int total_amount, amount_1s[12], amount_0s[12];

	total_amount = 1;
	for (int i  = 0; i < 12; i++)
	{
		amount_1s[i] = 0;
		amount_0s[i] = 0;
	}
	fd = open("diagnostic_report.txt", O_RDONLY);
	curr_line = get_next_line(fd);
	while (curr_line)
	{
		for (int i = 0; curr_line[i]; i++)
		{
			if (curr_line[i] == '1')
				amount_1s[i]++;
		}
		free (curr_line);
		curr_line = get_next_line(fd);
		total_amount++;
	}
	printf("the array after the while loop: ");
	for (int i = 0; i < 12; i++)
		printf(" [%d]", amount_1s[i]);
	printf("\n");
	for (int i = 0; i < 12; i++)
	{
		if (amount_1s[i] > (total_amount / 2))
		{
			amount_1s[i] = 1;
			amount_0s[i] = 0;
		}
		else
		{
			amount_1s[i] = 0;
			amount_0s[i] = 1;
		}
	}
	printf("the ponderated array_1s: ");
	for (int i = 0; i < 12; i++)
		printf(" [%d]", amount_1s[i]);
	printf("\n");
	printf("the ponderated array_0s: ");
	for (int i = 0; i < 12; i++)
		printf(" [%d]", amount_0s[i]);
	printf("\n");
	int binary_to_decimal_1 = 0;
	int binary_to_decimal_0 = 0;
	for (int i = 0; i < 12; i++)
	{
		if (amount_1s[i])
			binary_to_decimal_1 |= 0x1;
		if (amount_0s[i])
			binary_to_decimal_0 |= 0x1;
		if (i != 11)
		{
			binary_to_decimal_1 <<= 1;
			binary_to_decimal_0 <<= 1;
		}
	}
	printf("1s = %d\n0s = %d\n", binary_to_decimal_1, binary_to_decimal_0);
	printf("power consumption = %d\n", binary_to_decimal_0 * binary_to_decimal_1);
	close(fd);
}