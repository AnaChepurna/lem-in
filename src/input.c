#include "../lem_in.h"

int read_ants(int fd, s_board *board)
{
	char *str;
	int res;

	get_next_line(fd, &str);
	res = ft_atoi(str);
	while (IS_NUMBER(*str) || IS_SPACE(*str))
		str++;
	if (*str)
		return (0);
	board->num = res;
	return res;
}

static int parse_room_name(char *str, char **name)
{
	int i;

	i = 0;
	while (str[i] != ' ')
		i++;
	*name = ft_strsub(str, 0, i);
	return (i);
}

static int parse_room(char *str, char **name, int *x, int *y)
{
	if (ft_strequ("##start", str))
		return (1);
	if (ft_strequ("##end", str))
		return (2);
	if (ft_strnequ("#", str, 1))
		return (3);

	return (0);
}

int read_rooms(int fd, s_board *board)
{
	char *str;
	int se[2];
	int xy[2];
	char *name;

	se[0] = 0;
	se[1] = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (ft_strchr('-', str))
			break;
		if (!parse_room(str, &name, &xy[0], &xy[1]))
			ft_lstadd(&board->rooms,
				obj_in_lst(new_room(name, xy[0], xy[1])));
	}
	return (se[0] && se[1] ? 1 : 0);
}

int read_connections(int fd, s_board *board)
{
	return (0);
}