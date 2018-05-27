#include "../lem_in.h"

t_room		*new_room(void)
{
	t_room *room;

	if ((room = (t_room *)malloc(sizeof(t_room))))
	{
		room->name = '\0';
		room->y = 0;
		room->x = 0;
		room->way = NULL;
		room->connection = NULL;
		room->status = 0;
		room->order = 0;
	}
}

void		clear_room(void *r, size_t size)
{
	t_list	*lst1;
	t_list	*lst2;
	t_room	*room;

	void(size);
	room = (t_room *)r;
	lst1 = room->connection;
	while (lst1)
	{
		lst2 = lst1->next;
		free(lst1);
		lst1 = lst2;
	}
	free(r);
}

t_list		*obj_in_lst(void *obj)
{
	t_list	*lst;

	lst = ft_lstnew(NULL, 0);
	lst->content = obj;
	return (lst);
}

void		for_unlock_all_rooms(t_list *lst)
{
	t_room	*room;

	if (!lst)
		return;
	room = (t_room *)lst->content;
	if (room)
		room->status ^= R_LOCK;
}
