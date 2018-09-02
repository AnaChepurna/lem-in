/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:54:07 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 13:54:09 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_room		*new_room(char *name, int x, int y)
{
	t_room *room;

	if ((room = (t_room *)malloc(sizeof(t_room))))
	{
		room->name = name;
		room->y = y;
		room->x = x;
		room->connect = NULL;
		room->commited = NULL;
		room->status = 0;
		room->order = -1;
		room->lock = 0;
	}
	return (room);
}

void		clear_room(void *r, size_t size)
{
	t_list	*lst1;
	t_list	*lst2;
	t_room	*room;

	(void)size;
	room = (t_room *)r;
	lst1 = room->connect;
	while (lst1)
	{
		lst2 = lst1->next;
		free(lst1);
		lst1 = lst2;
	}
	lst1 = room->commited;
	while (lst1)
	{
		lst2 = lst1->next;
		free(lst1);
		lst1 = lst2;
	}
	if (room->name)
		free(room->name);
	free(r);
}

t_list		*obj_in_lst(void *obj)
{
	t_list	*lst;

	lst = ft_lstnew(NULL, 0);
	lst->content = obj;
	return (lst);
}

t_board		*new_board(void)
{
	t_board *res;

	if ((res = (t_board *)malloc(sizeof(t_board))))
	{
		res->num = 0;
		res->start = NULL;
		res->end = NULL;
		res->ants = NULL;
		res->rooms = NULL;
	}
	return (res);
}

void		clear_board(t_board **board)
{
	ft_lstdel(&(*board)->rooms, &clear_room);
	ft_lstdel(&(*board)->ants, &clear_ant);
	free(*board);
	*board = NULL;
}
