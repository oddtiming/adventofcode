#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
	int nb1, nb2, i;
	char *s1="10,31";

	i = 0;
	nb1 = atoi(s1);
	while (isdigit(s1[i]))
		i++;
	i++;
	printf("%d\n", i);
	nb2 = atoi((s1 + i));
	printf("nb1 = %d\nnb2 = %d\n", nb1, nb2);
}