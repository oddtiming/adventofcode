#include <stdio.h>
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

void	init_cards(int **cards)
{
	int		nb_lines, nb_cards;
	int		fd;
	char	*curr_line;

	fd = open("inputs.txt", O_RDONLY);
	curr_line = get_next_line(fd);
	free (curr_line);
	curr_line = get_next_line(fd);
	nb_lines = 0;
	nb_cards = 0;
	while (curr_line)
	{
		//if (ft_isdigit(curr_line[0]) || ft_isdigit(curr_line[1]))
			nb_lines++;
		printf("%s", curr_line);
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	printf("nb_lines = %d\n", nb_lines);
	//cards = malloc()
}

int	main(void)
{
	int		fd, nb_draws, j;
	int		*draws;
	char	*curr_line;
	int		**bingo_cards;
	int		**matched_cards;

	nb_draws = 0;
	j = 0;
	fd = open("inputs.txt", O_RDONLY);
	curr_line = get_next_line(fd);
	for (int i = 0; curr_line && curr_line[i] != '\n'; i++)
		if (curr_line[i] == ',')
			nb_draws++;
	nb_draws++;
	printf("nb_draws = %d\n", nb_draws);
	printf("curr_line = %s\n", curr_line);
	//nb + 1 for termination
	draws = malloc((nb_draws + 1) * sizeof(int));
	for (int i = 0; curr_line[i] != '\n'; )
	{
		if (curr_line[i] == ',')
			i++;
		draws[j] = atoi(curr_line + i);
		while (ft_isdigit(curr_line[i]))
			i++;
		j++;
	}
	draws[j] = -1;
	for (int i = 0; i <= j; i++)
		printf("draws[%d] = %d\n", i, draws[i]);
	free(curr_line);
	close(fd);
	init_cards(bingo_cards);
}