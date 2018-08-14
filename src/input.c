#include "../lem_in.h"

int read_ants(int fd, t_board *board)
{
	char *str;
	char *src;
	int res;

	get_next_line(fd, &src);
	str = src;
	res = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str)
		res = 0;
	board->num = res;
	if (res)
		ft_putendl(src);
	free(src);
	return res;
}

int  read_comment(char *str)
{
	if (ft_strequ("##start", str))
		return (R_START);
	if (ft_strequ("##end", str))
		return (R_END);
	if (ft_strnequ("#", str, 1))
		return (-1);
	return (0);
}

static char		*parse_name(char **str)
{
	int i;
	char *name;

	if (**str == 'L' || IS_SPACE(**str))
		return (NULL);
	i = 0;
	while (!IS_SPACE((*str)[i]))
		i++;
	name = ft_strsub(*str, 0, i);
	*str += i;
	return (name);
}

static int 		parse_coord(char **str)
{
	int res;

	if (**str == ' ')
		(*str)++;
	else
		return (-1);
	res = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	if (**str != ' ' || !**str)
		return (-1);
	return (res);
}

static t_room	*parse_room(char *str, int comment)
{
	char *name;
	int 	x;
	int 	y;
	t_room	*room;

	if (!(name = parse_name(&str)))
		return (NULL);
	x = parse_coord(&str);
	y = parse_coord(&str);
	if (x == -1 || y == -1 || *str)
	{
		free(name);
		return (NULL);
	}
	room = new_room(name, x, y);
	if (comment > 0 && room)
		room->status = comment;
	return (room);
}

int read_rooms(int fd, t_board *board)
{
	char *str;
	t_room *room;
	int 	comment;

	while (get_next_line(fd, &str) > 0)
	{
		room = NULL;
		if (ft_strchr(str, '-'))
			break;
		if ((comment = read_comment(str)))
		{
			ft_putendl(str);
			free(str);
			get_next_line(fd, &str);
		}
		if (!(room = parse_room(str, comment)))
			return (1);
		ft_lstadd(&(board->rooms), obj_in_lst(room));
		ft_putendl(str);
		free(str);
		str = NULL;
	}
	return (read_connections(fd, board, str));
}

int read_connections(int fd, t_board *board, char *str)
{
	(void)fd;
	(void)board;
	(void)str;
	return (0);
}