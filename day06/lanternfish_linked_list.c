#include "../libft/libft.h"
#include <fcntl.h>

void	lst_iter_oneday(void *content, t_list *lst_head)
{
	int	*int_buff;
	
	*(int *)content -= 1;
	if (*(int *)content < 0)
	{
		*(int *)content = 6;
		int_buff = malloc(sizeof(int));
		*int_buff = 8;
		ft_lstadd_back(&lst_head, ft_lstnew(int_buff));
	}
}

void	lst_del(void *content)
{
	free(content);
}

//Gave up on that solution because of the sheer TIME it consumed. Also gave the wrong answer ¯\_(ツ)_/¯
int	main(void)
{
	int		fd, read_status;
	char	*file_buff;
	t_list	*lst_head, *lst_ptr;
	int		*int_buff;
	void	(*decrease_fct)(void *, t_list *) = &lst_iter_oneday;
	void	(*del_fct)(void *) = &lst_del;

	fd = open("inputs.txt", O_RDONLY);
	file_buff = malloc(2);
	//reads the first digit
	read_status = read(fd, file_buff, 1);
	file_buff[1] = 0;
	int_buff = malloc(sizeof(int));
	*int_buff = atoi(file_buff);	
	lst_head = ft_lstnew(int_buff);
	//reads the first comma
	read_status = read(fd, file_buff, 1);
	//on to the second digit
	read_status = read(fd, file_buff, 1);
	file_buff[1] = 0;
	while (read_status)
	{
		int_buff = malloc(sizeof(int));
		*int_buff = ft_atoi(file_buff);
		ft_lstadd_back(&lst_head, ft_lstnew(int_buff));
		//reads the next comma, then the next digit
		read_status = read(fd, file_buff, 1);
		read_status = read(fd, file_buff, 1);
		file_buff[1] = 0;
	}
	close(fd);
	free(file_buff);
	
	printf("after adding all the inputs, list size = %d\n", ft_lstsize(lst_head));
	lst_ptr = lst_head;
	for (int i = 0; i < 300; i++)
	{
		printf("lst[%d] = %d\n", i, *(int *)lst_ptr->content);
		lst_ptr = lst_ptr->next;
	}

	for (int i = 0; i < 80; i++)
	{
		ft_lstiter_add(lst_head, decrease_fct);
	}
	printf("after 80 days, list size = %d\n", ft_lstsize(lst_head));

	lst_ptr = lst_head;
	for (int i = 0; lst_ptr; i++)
	{
		printf("lst[%d] = %d\n", i, *(int *)lst_ptr->content);
		lst_ptr = lst_ptr->next;
	}
	ft_lstclear(&lst_head, lst_del);
}