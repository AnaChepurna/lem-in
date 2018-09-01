/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 15:54:45 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 15:54:47 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		print_and_free(char *str)
{
	ft_putendl(str);
	free(str);
}

void			read_rooms(int fd, t_board *board)
{
	char	*str;
	t_room	*room;
	int		comment[2];

	str = NULL;
	while (get_next_line(fd, &str) > 0)
	{
		room = NULL;
		if (ft_strchr(str, '-'))
			break ;
		comment[1] = 0;
		while ((comment[0] = read_comment(str)))
		{
			comment[1] = comment[0] < -1 ? comment[0] : comment[1];
			print_and_free(str);
			get_next_line(fd, &str);
		}
		if (!(room = parse_room(str, comment[1])))
			return ;
		ft_lstadd(&(board->rooms), obj_in_lst(room));
		print_and_free(str);
		str = NULL;
	}
	read_connections(fd, board, str);
}

static t_room	*find_room(t_board *board, char *name)
{
	t_list	*lst;
	t_room	*room;

	lst = board->rooms;
	while (lst)
	{
		room = lst->content;
		if (ft_strequ(room->name, name))
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

static int		get_connection(t_board *board, char *name1, char *name2)
{
	t_room *room1;
	t_room *room2;

	room1 = find_room(board, name1);
	room2 = find_room(board, name2);
	if (!room1 || !room2)
		return (0);
	if (room2 != room1)
	{
		ft_lstadd(&room1->connect, obj_in_lst(room2));
		ft_lstadd(&room2->connect, obj_in_lst(room1));
	}
	return (1);
}

void			read_connections(int fd, t_board *board, char *str)
{
	char **arr;

	while (42)
	{
		if (!str && get_next_line(fd, &str) < 1)
			break ;
		if (!read_comment(str))
		{
			arr = ft_strsplit(str, '-');
			if (ft_arrlen((void **)arr) != 2 ||
				!get_connection(board, arr[0], arr[1]))
			{
				ft_arrfree(&arr);
				free(str);
				break ;
			}
			ft_arrfree(&arr);
		}
		ft_putendl(str);
		free(str);
		str = NULL;
	}
}
