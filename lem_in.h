/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:54:32 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 13:54:33 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <stdio.h>

# define R_START		-2
# define R_END			-3

typedef struct		s_room
{
	char			*name;
	int				y;
	int				x;
	t_list			*connect;
	int				status;
	t_list			*commited;
	int				order;
	int				lock;
}					t_room;

typedef struct		s_ant
{
	int				number;
	t_room			*location;
}					t_ant;

typedef struct		s_board
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
t_board				*new_board(void);
void				clear_board(t_board **board);

/*
**ants.c
*/
int					step_colony(t_list *lst, t_board *board);
t_list				*get_colony(int num, t_room *start);
void				clear_ant(void	*a, size_t size);
void				print_ant(t_ant *ant);

/*
**scout.c
*/
void				lock_room(t_room *locking);
int					need_lock(t_room *check);
void				number_rooms(t_room	*start);
int					scout_start_end(t_board *board);

/*
**input.c
*/
void				read_connections(int fd, t_board *board, char *str);
void				read_rooms(int fd, t_board *board);
int					read_ants(int fd, t_board *board);
int					read_comment(char *str);
t_room				*parse_room(char *str, int comment);
void				mark_roads(t_room *end);
void				print_room(t_room *room);
void				print_rooms(t_list *start);

/*
**branch.c
*/
void				add_commit(unsigned int status, t_room *road, t_room *room);
int					is_commited(t_room *road, t_room *room);
void				clear_commits(t_room *room, t_room *flag);
void				clear_unconnected(t_room *room, t_room *flag);

#endif
