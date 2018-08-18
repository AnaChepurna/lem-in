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

#include <stdio.h>

void print_rooms(t_board *board)
{
	t_list *lst;
	t_list *l;
	t_room *room;
	t_room *r;

	lst = board->rooms;
	while (lst)
	{
		room = lst->content;
		l = room->connect;
		if (room->status == R_START)
			printf("START\n");
		else if (room->status == R_END)
			printf("END\n");
		else
			printf("road $%i\n", room->status);
		printf("%s, %i %i\n", room->name, room->x, room->y);
		printf("order is %i\n", room->order);
		while (l)
		{
			r = l->content;
			printf("%s; ", r->name);
			l = l->next;
		}
		printf("\n--------\n");
		lst = lst->next;
	}
}