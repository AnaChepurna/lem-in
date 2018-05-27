#include "../lem_in.h"

static t_ant	*new_ant(void)
{
	return ((t_ant *)malloc(sizeof(t_ant)));
}

void			clear_ant(void	*a, size_t size)
{
	(void)size;
	free(a);
}

t_list		*get_colony(int num, t_room *start)
{
	t_list	*lst;
	t_ant	*ant;
	int		i;

	lst = NULL;
	i = 0;
	while (++i <= num)
	{
		ant = new_ant();
		ant->number = i;
		ant->location = start;
		ft_lstaddend(&lst, obj_in_lst((void *)ant));
	}
	return (lst);
}

static int		step_ant(t_ant *ant)
{
	if (ant)
	{
		if (ant->location->status & R_END)
			return (2);
		if (ant->location->way->status & R_LOCK)
			return (0);
		ant->location->status ^= R_LOCK;
		ant->location = ant->location->way;
		if (ant->location->status & R_END)
			return (2);
		ant->location->status |= R_LOCK;
		return (1);
	}
	return (0);
}

int				step_colony(t_list *lst)
{
	int		status;
	int		ret;

	status = 1;
	while (lst)
	{
		if (!(ret = step_ant((t_ant *)lst->content)))
			return (0);
		if (ret == 1)
			status = 0;
		lst = lst->next;
	}
	return (status)
}
