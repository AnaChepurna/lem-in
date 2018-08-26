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

3
##start
st 1 2
##end
en 5 4
1 1 1
2 2 2
3 3 3
4 4 4
st-1
st-2
1-3
1-4
3-en
4-en