#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

//Takes as an argument the number of days since inception. If no argument is passed, takes it as 80
int	main(int argc, char* argv[])
{
	unsigned long	fish_array[9] = { 0 };
	int				fd, read_status, int_temp;
	char			*file_buff;
	unsigned long	total_fish = 0;
	unsigned long	reproducing_fish = 0;
	int				nb_days;

	if (argc > 1)
		nb_days = atoi(argv[argc - 1]);
	else
		nb_days = 80;

	fd = open("inputs.txt", O_RDONLY);
	file_buff = malloc(3);
	//Well that's one way to parse a csv... 1 misplaced comma and I'm fucked, but it works.
	read_status = read(fd, file_buff, 2);
	while (read_status)
	{
		int_temp = file_buff[0] - '0';
		fish_array[int_temp]++;
		read_status = read(fd, file_buff, 2);
	}
	close(fd);
	free(file_buff);

	for (int i = 0; i < 9; i++)
	{
		// printf("array[%d] = %d\n", i, fish_array[i]);
		total_fish += fish_array[i];
	}
	printf("\nTotal fish at beginning = %lu\n", total_fish);
	total_fish = 0;

	//Modifies the value of fish at any given day of reproductive cycle.
	//reproducing_fish will increase both the value of fish 7 and 9 days away from reproducing
	for (int i = 0; i < nb_days; i++)
	{
		reproducing_fish = fish_array[0];
		for (int j = 0; j < 8; j++)
			fish_array[j] = fish_array[j + 1];
		fish_array[6] += reproducing_fish;
		fish_array[8] = reproducing_fish;
	}
	
	for (int i = 0; i < 9; i++)
	{
		// printf("array[%d] = %d\n", i, fish_array[i]);
		total_fish += fish_array[i];
	}

	printf("\nTotal fish after %d days = %lu\n", nb_days, total_fish);
}