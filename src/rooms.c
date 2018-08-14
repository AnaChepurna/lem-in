#include "../lem_in.h"

// t_room		*new_room(char name, int x, int y)
// {
// 	t_room *room;

// 	if ((room = (t_room *)malloc(sizeof(t_room))))
// 	{
// 		room->name = name;
// 		room->y = y;
// 		room->x = x;
// 		room->connect = NULL;
// 		room->status = 0;
// 		room->order = 0;
// 	}
// }

// void		clear_room(void *r, size_t size)
// {
// 	t_list	*lst1;
// 	t_list	*lst2;
// 	t_room	*room;

// 	void(size);
// 	room = (t_room *)r;
// 	lst1 = room->connect;
// 	while (lst1)
// 	{
// 		lst2 = lst1->next;
// 		free(lst1);
// 		lst1 = lst2;
// 	}
// 	free(r);
// }

// t_list		*obj_in_lst(void *obj)
// {
// 	t_list	*lst;

// 	lst = ft_lstnew(NULL, 0);
// 	lst->content = obj;
// 	return (lst);
// }
