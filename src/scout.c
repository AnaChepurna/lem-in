#include "../lem_in.h"

void		number_rooms(t_room	*start)
{
	t_list	*lst;
	t_room	*room;

	lst = start->connect;
	while (lst)
	{
		room = (t_room *)lst->content;
		if (!(room->status & R_START) && !(room->status & R_END))
		{
			if (room->order < 0 || room->order > start->order)
			{
				room->order = start->order + 1;
				number_rooms(room);
			}
		}
		lst = lst->next;
	}
}

int scout_start_end(t_board *board)
{
	t_list *lst;
	t_room *room;

	lst = board->rooms;
	while (lst)
	{
		room = lst->content;
		if (room->status == R_START && !board->start)
			board->start = room;
		else if (room->status == R_START && board->start)
				return (6);
		if (room->status == R_END && !board->end)
			board->end = room;
		else if (room->status == R_END && board->end)
				return (7);
		lst = lst->next;	
	}
	if (!board->end)
		return (8);
	if (!board->start)
		return (9);
	return (0);
}

static int mark_road(t_room *road, int status)
{
	t_room *next;
	t_list *lst;

	road->status = status;
	lst = road->connect;
	while (lst)
	{
		next = lst->content;
		if (next->status == R_START)
			return (1);
		if (!next->status && next->order < road->order
			&& mark_road(next, status))
			break;
		next = NULL;
		lst = lst->next;
	}
	if (!next)
	{
		road->status = 0;
		return (0);
	}
	return (1);
}

int 	sort_roads(t_list *al, t_list *bl)
{
	t_room *a;
	t_room *b;

	a = al->content;
	b = bl->content;
	if (a->order > b->order)
		return (1);
	return (0);
}

int		mark_roads(t_room *end)
{
	t_list *lst;
	t_room *room;
	int road_number;

	road_number = 0;
	lst = end->connect;
	sort_lst(lst, sort_roads);
	while (lst)
	{
		room = lst->content;
		if (room->order > 0)
			road_number += mark_road(room, room->order);
		lst = lst->next;
	}
	return (road_number);
}