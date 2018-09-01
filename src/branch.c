/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:53:26 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 13:53:29 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			is_commited(t_room *road, t_room *room)
{
	t_list	*lst;

	if (!road)
		return (0);
	lst = room->commited;
	while (lst)
	{
		if (lst->content == road)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void		add_commit(unsigned int status, t_room *road, t_room *room)
{
	t_list	*new;

	if (is_commited(road, room))
		return ;
	new = ft_lstnew(NULL, 0);
	new->content = road;
	new->content_size = status;
	ft_lstaddend(&room->commited, new);
}

static void	refresh_commits(t_room *road, t_room *flag)
{
	t_list	*lst;
	t_list	*lst1;

	lst = road->commited;
	while (lst)
	{
		lst1 = lst;
		lst = lst->next;
		free(lst1);
	}
	road->commited = NULL;
	add_commit(flag->order, flag, road);
}

void		clear_commits(t_room *room, t_room *flag)
{
	t_list	*lst;
	t_room	*r;
	t_room	*road;
	int		roads;

	roads = 0;
	if (!room->commited)
		return ;
	lst = room->connect;
	while (lst)
	{
		r = lst->content;
		if (r->status == R_END)
			refresh_commits(room, flag);
		else if (r->status != R_START && r->order < room->order
			&& is_commited(flag, r))
		{
			roads++;
			road = r;
			clear_commits(r, flag);
		}
		lst = lst->next;
	}
	if (roads == 1)
		refresh_commits(road, flag);
}

void		clear_unconnected(t_room *room, t_room *flag)
{
	t_list	*lst;
	t_list	*lst1;
	t_room	*r;
	int		commited;

	commited = 0;
	lst = room->connect;
	while (lst)
	{
		r = lst->content;
		if (r && r->status != R_END && r->order < room->order &&
			is_commited(flag, r) && commited++)
		{
			lst1 = r->commited;
			while (lst1)
			{
				if (lst1->content == flag)
					lst1->content = NULL;
				lst1 = lst1->next;
			}
		}
		if (r && r->order < room->order)
			clear_unconnected(r, flag);
		lst = lst->next;
	}
}
