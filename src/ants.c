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

static void 		paste_room(t_ant *ant, t_board *board, t_room *room)
{
	if (ant->location == board->start)
		board->num--;
	else
		ant->location->lock = 0;
	ant->location = room;
	if (ant->location->status != R_END)
		ant->location->lock = 1;
}

static int		search_room(t_ant *ant, t_board *board, t_room *road)
{
	t_list *lst1;
	t_room *room;

	lst1 = ant->location->connect;
	while (lst1)
	{
		room = lst1->content;
		if (room->status == R_END)
		{
			paste_room(ant, board, room);
			return (1);
		}
		lst1 = lst1->next;
	}
	lst1 = ant->location->connect;
	while (lst1)
	{
		room = lst1->content;
		if (!room->lock && room->status != R_START && 
			room->order > ant->location->order && is_commited(road, room))
		{
			paste_room(ant, board, room);
			return (1);
		}
		lst1 = lst1->next;
	}
	return (0);
}

static int		start_ant(t_ant *ant, t_board *board)
{
	t_list *lst;
	t_room *road;
	unsigned int 	status;

	lst = ant->location->commited;
	while (lst)
	{
		if ((int)lst->content_size > board->num)
			break;
		road = lst->content;
		if (search_room(ant, board, road))
			return (1);
		lst = lst->next;
	}
	lst = ant->location->commited;
	status = lst->content_size;
	while (lst)
	{
		if (status < lst->content_size)
			break ;
		road = lst->content;
		if (search_room(ant, board, road))
			return (1);
		lst = lst->next;
	}
	return (0);

	// road = NULL;
	// lst = ant->location->connect;
	// while (lst)
	// {
	// 	room = lst->content;
	// 	if (room->status <= board->num && !room->lock &&
	// 		room->status)
	// 		road = room;
	// 	lst = lst->next;
	// }
	// if (!road)
	// {
	// 	lst = ant->location->connect;
	// 	while (lst)
	// 	{
	// 		room = lst->content;
	// 		if (room->status && (!road || room->status < road->status))
	// 			road = room;
	// 		lst = lst->next;
	// 	}
	// }
	// if (road && !road->lock)
	// {
	// 	board->num--;
	// 	ant->location = road;
	// 	ant->location->lock = 1;
	// }
}

// static void     road_ant(t_ant *ant)
// {
// 	t_list *lst;
// 	t_room *room;

// 	lst = ant->location->connect;
// 	while (lst)
// 	{
// 		room = lst->content;
// 		if (!room->lock && room->order > ant->location->order &&
// 			room->status == ant->location->status)
// 		{
// 			ant->location->lock = 0;
// 			ant->location = room;
// 			ant->location->lock = 1;
// 			//printf(GREEN "step\n" RESET);
// 			return ;
// 		}
// 		if (room->status == R_END)
// 		{
// 			ant->location->lock = 0;
// 			ant->location = room;
// 			return ;
// 		}
// 		lst = lst->next;
// 	}
// 	//printf( YELLOW "stay\n" RESET);
// }

static int		step_ant(t_ant *ant, t_board *board)
{
	if (ant->location->status == R_END)
		return (1);
	// printf(MAGENTA"\nant and location\n" RESET);
	// print_ant(ant);
	// print_room(ant->location);
	// printf(GREEN"\n?????????\n" RESET);

	// if (ant->location->status == R_START)
	// else
	// 	road_ant(ant);
	if (start_ant(ant, board) && ant->location->status != R_START)
	{
		//print_room(ant->location);
		print_ant(ant);
	}
	else
		return (-1);
	// printf(RED "\n-------------\n" RESET);
	if (ant->location->status == R_END)
		return (1);
	return (0);
}

int				step_colony(t_list *lst, t_board *board)
{
	static int	num = 0;
	int status;

	if (!num)
		num = board->num;
	status = 0;
	while (lst)
	{
		status += step_ant((t_ant *)lst->content, board);
		if (status == -1)
			return (0);
		lst = lst->next;
	}
	return (status == num);
}
