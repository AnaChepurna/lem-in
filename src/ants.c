#include "../lem_in.h"

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
		if ((ant = (t_ant *)malloc(sizeof(t_ant))))
		{
			ant->number = i;
			ant->location = start;
			ft_lstaddend(&lst, obj_in_lst((void *)ant));
		}
	}
	return (lst);
}

static t_room	*get_way(int order, t_list *lst)
{
	t_room	*room;

	while (lst)
	{
		room = (t_room *)lst->content;
		if (room->status & R_END)
			return (room);
		if (room->order >= order && !(IS_LOCK(room->status)))
			return (room);
		lst = lst->next;
	}
	return (NULL);
}

static int		step_ant(t_ant *ant)
{
	t_room	*way;

	if (ant)
	{
		if (ant->location->status & R_END)
			return (1);
		if ((way = get_way(ant->location->order, ant->location->connect)))
		{
			ant->location->status ^= R_ALOCK;
			ant->location = way;
			if (ant->location->status & R_END)
				return (1);
			ant->location->status |= R_ALOCK;
		}
	}
	return (0);
}

int				step_colony(t_list *lst)
{
	int		status;

	status = 1;
	while (lst)
	{
		if (!step_ant((t_ant *)lst->content))
			status = 0;
		lst = lst->next;
	}
	return (status)
}
