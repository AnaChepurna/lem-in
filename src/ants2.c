/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:16:35 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 16:16:37 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		paste_room(t_ant *ant, t_board *board, t_room *room)
{
	if (ant->location == board->start)
		board->num--;
	else
		ant->location->lock = 0;
	ant->location = room;
	if (ant->location->status != R_END)
		ant->location->lock = 1;
	return (1);
}

static int		search_room(t_ant *ant, t_board *board, t_room *road)
{
	t_list	*lst1;
	t_room	*room;

	lst1 = ant->location->connect;
	while (lst1)
	{
		room = lst1->content;
		if (room->status == R_END && paste_room(ant, board, room))
			return (1);
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
	t_list			*lst;
	t_room			*road;

	lst = ant->location->commited;
	while (lst)
	{
		if ((int)lst->content_size > board->num)
			break ;
		road = lst->content;
		if (search_room(ant, board, road))
			return (1);
		lst = lst->next;
	}
	lst = ant->location->commited;
	while (lst)
	{
		if (ant->location->commited->content_size < lst->content_size)
			break ;
		road = lst->content;
		if (search_room(ant, board, road))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static int		step_ant(t_ant *ant, t_board *board)
{
	if (ant->location->status == R_END)
		return (1);
	if (start_ant(ant, board) && ant->location->status != R_START)
		print_ant(ant, ant->location);
	else
		return (-1);
	if (ant->location->status == R_END)
		return (1);
	return (0);
}

int				step_colony(t_list *lst, t_board *board)
{
	static int	num = 0;
	int			status;

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
