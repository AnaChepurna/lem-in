#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef struct		s_room
{
	char			name;
	int				y;
	int				x;
	t_room			*way;
	t_list			*connection;
	int				status;
	int				order;
}					t_room;

/*
**rooms.c
*/
t_room				*new_room(void);


#endif