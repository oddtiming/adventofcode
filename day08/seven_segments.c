#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>

int	is_set(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

//Needs to be corrected to avoid freeing errors;
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && *arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr && *arr)
	{
		free(arr[i]);
		free(arr);
	}
}

char	*get_next_word(const char *str, const char *sep)
{
	static int	i;
	int			word_len;
	char		*next_word;

	if (!str)
	{
		i = 0;
		return (NULL);
	}
	word_len = 0;
	while (str[i] && !is_set(str[i], sep))
	{
		i++;
		word_len++;
	}
	next_word = malloc(word_len + 1);
	i -= word_len;
	word_len = 0;
	while (str[i] && !is_set(str[i], sep))
	{
		next_word[word_len] = str[i];
		i++;
		word_len++;
	}
	next_word[word_len] = 0;
	if (str[i])
		i++;
	else
		i = 0;
	return (next_word);
}

char	**parse_line(char *curr_line)
{
	int		i;
	char	**input_digits;

	i = 0;
	input_digits = malloc(11 * sizeof(char *));
	while (i < 10)
	{
		input_digits[i] = get_next_word(curr_line, " ");
		i++;
	}
	get_next_word(NULL, "");
	input_digits[i] = NULL;
	return (input_digits);
}

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

//no diff with both ==> 9
//no diff with 1 ==> 0 (b/c 5 has only 1 diff with 4)
void	decipher_6s(char **char_inputs, int **int_values, int *str_len6)
{
	int	i, diff3over0, diff3over1, diff3over2;

	i = 0;
	//get_diff_charset will return 0 if s1 == 3 and s2 == 9
	diff3over0 = get_diff_charset(char_inputs[*(*int_values + 3)], char_inputs[str_len6[0]]);
	diff3over1 = get_diff_charset(char_inputs[*(*int_values + 3)], char_inputs[str_len6[1]]);
	diff3over2 = get_diff_charset(char_inputs[*(*int_values + 3)], char_inputs[str_len6[2]]);
	if (!diff3over0)
	{
		*(*int_values + 9) = str_len6[0];
		//1 diff with 1 ==> 6
		if (get_diff_charset(char_inputs[*(*int_values + 1)], char_inputs[str_len6[1]]) == 0)
		{
			*(*int_values + 0) = str_len6[1];
			*(*int_values + 6) = str_len6[2];
			return ;
		}
		else
		{
			*(*int_values + 0) = str_len6[2];
			*(*int_values + 6) = str_len6[1];
			return ;
		}
	}
	else if (!diff3over1)
	{
		*(*int_values + 9) = str_len6[1];
		//1 diff with 1 ==> 6
		if (get_diff_charset(char_inputs[*(*int_values + 1)], char_inputs[str_len6[0]]) == 0)
		{
			*(*int_values + 0) = str_len6[0];
			*(*int_values + 6) = str_len6[2];
			return ;
		}
		else
		{
			*(*int_values + 0) = str_len6[2];
			*(*int_values + 6) = str_len6[0];
			return ;
		}
	}
	else if (!diff3over2)
	{
		*(*int_values + 9) = str_len6[2];
		//1 diff with 1 ==> 6
		if (get_diff_charset(char_inputs[*(*int_values + 1)], char_inputs[str_len6[0]]) == 0)
		{
			*(*int_values + 0) = str_len6[0];
			*(*int_values + 6) = str_len6[1];
			return ;
		}
		else
		{
			*(*int_values + 0) = str_len6[1];
			*(*int_values + 6) = str_len6[0];
			return ;
		}
	}
}

void	decipher_5s(char **char_inputs, int **int_values, int *str_len5)
{
	int	i, diff01, diff12, diff02;

	i = 0;
	diff01 = get_diff_charset(char_inputs[str_len5[0]], char_inputs[str_len5[1]]);
	diff12 = get_diff_charset(char_inputs[str_len5[1]], char_inputs[str_len5[2]]);
	diff02 = get_diff_charset(char_inputs[str_len5[0]], char_inputs[str_len5[2]]);
	if (diff01 == 1)
	{
		if (diff02 == 1)
		{
			*(*int_values + 3) = str_len5[0];
			if (get_diff_charset(char_inputs[str_len5[2]], char_inputs[*(*int_values + 4)]) == 2)
			{
				*(*int_values + 5) = str_len5[2];
				*(*int_values + 2) = str_len5[1];
				return ;
			}
			else
			{
				*(*int_values + 5) = str_len5[1];
				*(*int_values + 2) = str_len5[2];
				return ;
			}
		}
		else if (diff12 == 1)
		{
			*(*int_values + 3) = str_len5[1];
			if (get_diff_charset(char_inputs[str_len5[2]], char_inputs[*(*int_values + 4)]) == 2)
			{
				*(*int_values + 5) = str_len5[2];
				*(*int_values + 2) = str_len5[0];
				return ;
			}
			else
			{
				*(*int_values + 5) = str_len5[0];
				*(*int_values + 2) = str_len5[2];
				return ;
			}
		}
	}
	//Means str_len5[0] and str_len5[1] are 2 and 5
	//		str_len5[2] is 3
	else 
	{
		*(*int_values + 3) = str_len5[2];
		if (get_diff_charset(char_inputs[str_len5[0]], char_inputs[*(*int_values + 4)]) == 2)
		{
			*(*int_values + 5) = str_len5[0];
			*(*int_values + 2) = str_len5[1];
			return ;
		}
		else
		{
			*(*int_values + 5) = str_len5[1];
			*(*int_values + 2) = str_len5[0];
			return ;
		}
	}
}

void	decipher_inputs(char **char_inputs, int **int_values)
{
	int		i, i5, i6, word_len;
	int		*str_len5, *str_len6;

	i = 0;
	i5 = 0;
	i6 = 0;
	word_len = 0;
	str_len5 = malloc(3 * sizeof(int));
	str_len6 = malloc(3 * sizeof(int));
	while (i < 10)
	{
		word_len = strlen(char_inputs[i]);
		if (word_len == 2)
			*(*int_values + 1) = i;
		else if (word_len == 3)
			*(*int_values + 7) = i;
		else if (word_len == 4)
			*(*int_values + 4) = i;
		else if (word_len == 5)
			str_len5[i5++] = i;
		else if (word_len == 6)
			str_len6[i6++] = i;
		else if (word_len == 7)
			*(*int_values + 8) = i;
		i++;
	}
	decipher_5s(char_inputs, int_values, str_len5);
	decipher_6s(char_inputs, int_values, str_len6);
}

void	reverse_indices(int *int_values)
{
	int buffer[10];
	int	i;

	i = 0;
	while (i < 10)
	{
		buffer[i] = int_values[i];
		i++;
	}
	i = 0;
	while (i < 10)
	{
		*(int_values + buffer[i]) = i;
		i++;
	}
}

int	get_abs_diff(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n != strlen(s2))
		return (1);
	while (i < n)
	{
		if (!is_set(s1[i], s2))
			return (1);
		i++; 
	}
	return (0);
}

int	get_digit(char *curr_digit, int word_len, char **char_inputs)
{
	int	i;

	i = 0;
	while (get_abs_diff(curr_digit, char_inputs[i], word_len))
		i++;
	return (i);
}

int	solve_line(char **char_inputs, char *curr_line, int *int_values)
{
	int		i;
	int		multiplier, result, curr_digit;
	int		word_len;

	i = 0;
	result = 0;
	multiplier = 1000;
	//I now want to search from word index to digit value
	reverse_indices(int_values);
	while (curr_line[++i] != '|') ;
	while (!isalpha(curr_line[++i])) ;
	while (multiplier && curr_line[i])
	{
		word_len = 0;
		while (isalpha(curr_line[i]))
		{
			i++;
			word_len++;
		}
		curr_digit = get_digit(curr_line + i - word_len, word_len, char_inputs);
		result += multiplier * int_values[curr_digit];
		multiplier /= 10;
		while (!isalpha(curr_line[i]))
			i++;
	}
	return (result);
}

int	main(void)
{
	int		fd;
	int		total_result, curr_result;
	char	*curr_line;
	char	**char_inputs;
	int		*int_values;

	fd = open("input.txt", O_RDONLY);
	curr_line = get_next_line(fd);
	total_result = 0;
	int_values = malloc(10 * sizeof(int));
	while (curr_line)
	{
		char_inputs = parse_line(curr_line);
		printf("%s", curr_line);
		for (int i = 0; i < 10; i++)
			printf("%s\n", char_inputs[i]);
		decipher_inputs(char_inputs, &int_values);
		curr_result = solve_line(char_inputs, curr_line, int_values);
		printf("%s = %d\n", curr_line, curr_result);
		total_result += curr_result;
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	close(fd);
	printf("Total = %d\n", total_result);
	
	// for (i = 0; char_inputs[i]; i++)
	// 	printf("line #%d: %s\n", i, char_inputs[i]);
	// free_array(char_inputs);
	// free(int_values);
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