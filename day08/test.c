#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>

int	get_diff_charset(const char *s1, const char *s2)
{
	int i = 0;
	int j = 0;
	int	diff = 0;
	int found = 0;

	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				found = 1;
			j++;
		}
		if (!found)
			diff++;
		found = 0;
		i++;
	}
	return (diff);
}

int	main(void)
{
	char *s1 = "abcd";
	char *s2 = "abce";
	
	printf("Diff btw '%s' && '%s' = %d\n", s1, s2, get_diff_charset(s1, s2));
	return (0);
}