/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:54:22 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 13:54:24 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		number_rooms(t_room *start)
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

int			scout_start_end(t_board *board)
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
	board->start->order = 0;
	return (0);
}

static void	mark_road(t_room *road, t_room *flag, int status)
{
	t_room *next;
	t_list *lst;

	add_commit(status, flag, road);
	if (road->status == R_START)
		return ;
	lst = road->connect;
	while (lst)
	{
		next = lst->content;
		if (next->order < road->order)
			mark_road(next, flag, status);
		lst = lst->next;
	}
}

int			sort_roads(t_list *al, t_list *bl)
{
	t_room *a;
	t_room *b;

	a = al->content;
	b = bl->content;
	if (a->order > b->order)
		return (1);
	return (0);
}

void		mark_roads(t_room *end)
{
	t_list *lst;
	t_room *room;

	lst = end->connect;
	sort_lst(lst, &sort_roads);
	while (lst)
	{
		room = lst->content;
		if (room->order > 0)
			mark_road(room, room, room->order);
		lst = lst->next;
	}
	lst = end->connect;
	while (lst)
	{
		room = lst->content;
		clear_commits(room, room);
		clear_unconnected(room, room);
		lst = lst->next;
	}
}
