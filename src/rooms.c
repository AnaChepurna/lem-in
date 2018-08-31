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

t_board *new_board(void)
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

void	clear_board(t_board **board)
{
	ft_lstdel(&(*board)->rooms, &clear_room);
	ft_lstdel(&(*board)->ants, &clear_ant);
	free(*board);
	*board = NULL;
}

//
//
//
//

void print_room(t_room *room)
{
	printf("//////\n%s %i %i\n", room->name, room->x, room->y);
	if (room->status == R_START)
		printf("start\n");
	else if (room->status == R_END)
		printf("end\n");
	//else printf("status %i\n", room->status);
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
	lst = room->commited;
	printf("commited: ");
	while (lst)
	{
		t_room *r = lst->content;
		printf("%s(%zi), ",r->name, lst->content_size);
		lst = lst->next;
	}
	printf("\n");
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