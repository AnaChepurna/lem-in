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

//
//
//
//

void print_room(t_room *room)
{
	printf("//////%s %i %i\n", room->name, room->x, room->y);
	if (room->status == R_START)
		printf("start\n");
	else if (room->status == R_END)
		printf("end\n");
	else printf("status %i\n", room->status);
	printf("order %i\n", room->order);
	printf("is lock ? %i\n", room->lock);
	printf("connections: ");
	t_list *lst = room->connect;
	while (lst)
	{
		t_room *r = lst->content;
		printf("%s, ", r->name);
		lst = lst->next;
	}
}

void print_rooms(t_list *rooms)
{
	t_room *room;
	t_list *lst;

	lst = rooms;
	while (lst)
	{
		room = lst->content;
		print_room(room);
		lst = lst->next;
	}
}