#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef	struct	s_riskmap{
	char	*map;
	size_t	y_max = 0;
	size_t	x_max = 0;
	size_t	lowest_risk = UINT_MAX;
}	t_riskmap;

void	find_safest_path(t_riskmap *riskmap, size_t curr_risk)
{
	size_t	x_curr = 0;
	size_t	y_curr = 0;

/*
	Stopped here.

	todo:
	- write recursive algorithm to exhaust all possible paths. Could write a try_left()/try_right()
		Need to know when to exit and what to return to which function.
*/

	while ()
}

int	main(void)
{
	t_riskmap	*riskmap;
	int			fd, filesize, i;
	char		read_buff;
	size_t		curr_risk = 0;

	filesize = 0;
	riskmap = malloc(sizeof(t_riskmap));
	fd = open("inputs.txt", O_RDONLY);
	while (read(fd, &read_buff, 1))
		filesize++;
	clode (fd);
	riskmap->map = malloc((filesize + 1) * sizeof(char));
	fd = open("inputs.txt", O_RDONLY);
	for (i = 0; read(fd, &read_buff, 1); i++)
	{
		riskmap->map[i] = read_buff;
		if (!x_max && read_buff = '\n')
			x_max = i;
	}
	riskmap->map[i] = 0;
	y_max = filesize / x_max;
	close (fd);

	find_safest_path(riskmap, curr_risk);

	free(riskmap->map);
	free(riskmap);
	return (0);
}
