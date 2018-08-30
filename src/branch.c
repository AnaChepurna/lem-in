#include "../lem_in.h"

int	is_commited(t_room *road, t_room *room)
{
	t_list *lst;

	lst = room->commited;
	while (lst)
	{
		if (lst->content == road)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	add_commit(unsigned int status, t_room *road, t_room *room)
{
	t_list *new;

	if (is_commited(road, room))
		return ;
	new = ft_lstnew(NULL, 0);
	new->content = road;
	new->content_size = status;
	ft_lstaddend(&room->commited, new);
}

// void	delete_commit(unsigned int status, t_room *room)
// {
// 	t_list *lst;
// 	t_list *lst1;

// 	if (room->commited->content_size == status)
// 	{
// 		lst = room->commited->next;
// 		free(room->commited);
// 		room->commited = lst;
// 		return ;
// 	}
// 	lst = room->commited;
// 	while (lst)
// 	{
// 		lst1 = lst->next;
// 		if (lst1->content_size == status)
// 		{
// 			lst->next = lst1->next;
// 			free(lst1);
// 			return ;
// 		}
// 		lst = lst->next;
// 	}
// }

static void refresh_commits(t_room *road, t_room *flag)
{
	t_list *lst;
	t_list *lst1;

	lst = road->commited;
	while(lst)
	{
		lst1 = lst;
		lst = lst->next;
		free(lst1);
	}
	road->commited = NULL;
	add_commit(flag->order, flag, road);
}

void	clear_commits(t_room *room, t_room *flag)
{
	t_list *lst;
	t_room *r;
	t_room *road;
	int		roads;

	roads = 0;
	lst = room->connect;
	while (lst)
	{
		r = lst->content;
		if (r->status == R_START)
			return ;
		if (r->order < room->order &&
		r->status != R_END && is_commited(flag, r))
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