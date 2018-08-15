#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

# define	R_START			1
# define	R_END			2
# define	R_ALOCK			4
# define	R_GLOCK			8
# define	IS_LOCK(n)		((n) & R_ALOCK || (n) & R_GLOCK)

typedef struct		s_room
{
	char			*name;
	int				y;
	int				x;
	t_list			*connect;
	int				status;
	int				order;
}					t_room;

typedef struct		s_ant
{
	int				number;
	t_room			*location;
}					t_ant;

typedef struct 		s_board
{
	int				num;
	t_room			*start;
	t_room			*end;
	t_list			*ants;
	t_list			*rooms;
}					t_board;

/*
**rooms.c
*/
t_room				*new_room(char *name, int x, int y);
void				clear_room(void *r, size_t size);
t_list				*obj_in_lst(void *obj);

/*
**ants.c
*/
int					step_colony(t_list *lst);
t_list				*get_colony(int num, t_room *start);
void				clear_ant(void	*a, size_t size);

/*
**scout.c
*/
void				lock_room(t_room *locking);
int					need_lock(t_room *check);
void				number_rooms(t_room	*start);

/*
**input.c
*/
void 				read_connections(int fd, t_board *board, char *str);
void 				read_rooms(int fd, t_board *board);
int 				read_ants(int fd, t_board *board);
int 				read_comment(char *str);


void print_rooms(t_board *board);

#endif