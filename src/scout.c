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

// int			need_lock(t_room *check)
// {
// 	t_list	*lst;
// 	t_room	*room;

// 	lst = room->connect;
// 	while (lst)
// 	{
// 		room = (t_room *)lst->content;
// 		if (room->status & R_END)
// 			return (0);
// 		if (!(room->status & R_GLOCK) && room->order >= check->status)
// 			return (0);
// 		lst = lst->next;
// 	}
// 	return (1);
// }

// void		lock_room(t_room *locking)
// {
// 	t_list	*lst;
// 	t_room	*room;

// 	if (!locking)
// 		return;
// 	locking->status |= R_GLOCK;
// 	lst = locking->connect;
// 	while (lst)
// 	{
// 		room = (t_room *)lst->content;
// 		if (need_lock(room))
// 			lock_room(room);
// 		lst = lst->next;
// 	}
// }

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
				return (2);
		if (room->status == R_END && !board->end)
			board->end = room;
		else if (room->status == R_END && board->end)
				return (2);
		lst = lst->next;	
	}
	if (!board->end || !board->start)
		return (2);
	return (0);
}