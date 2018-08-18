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

static void print_ant(t_ant *ant)
{
	ft_putstr("L");
	ft_putnbr(ant->number);
	ft_putstr("-");
	ft_putstr(ant->location->name);
	ft_putstr(" ");
}

static void		start_ant(t_ant *ant, t_board *board)
{
	t_list *lst;
	t_room *road;
	t_room *room;

	road = NULL;
	lst = ant->location->connect;
	while (lst)
	{
		room = lst->content;
		if (room->status <= board->num && !room->lock)
			road = room;
		lst = lst->next;
	}
	if (!road)
	{
		lst = ant->location->connect;
		while (lst)
		{
			room = lst->content;
			if (!road || room->status < road->status)
				road = room;
			lst = lst->next;
		}
	}
	if (road && !road->lock)
	{
		board->num--;
		ant->location = road;
		ant->location->lock = 1;
	}
}

static void     road_ant(t_ant *ant)
{
	t_list *lst;
	t_room *room;

	lst = ant->location->connect;
	while (lst)
	{
		room = lst->content;
		if (!room->lock && room->order > ant->location->order &&
			room->status == ant->location->status)
		{
			ant->location->lock = 0;
			ant->location = room;
			ant->location->lock = 1;
			break;
		}
		if (room->status == R_END)
		{
			ant->location->lock = 0;
			ant->location = room;
			break;
		}
		lst = lst->next;
	}
}

static int		step_ant(t_ant *ant, t_board *board)
{
	if (ant->location->status == R_END)
		return (1);
	if (ant->location->status == R_START)
		start_ant(ant, board);
	else
		road_ant(ant);
	if (ant->location->status != R_START)
		print_ant(ant);
	if (ant->location->status == R_END)
		return (1);
	return (0);
}

int				step_colony(t_list *lst, t_board *board)
{
	int		status;

	status = 1;
	while (lst)
	{
		status = step_ant((t_ant *)lst->content, board);
		lst = lst->next;
	}
	return (status);
}
