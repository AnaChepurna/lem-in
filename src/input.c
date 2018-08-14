#include "../lem_in.h"

int read_ants(int fd, t_board *board)
{
	char *str;
	char *src;
	int res;

	get_next_line(fd, &src);
	ft_putendl(src);
	str = src;
	while (ft_isdigit(*str))
		str++;
	res = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	while (IS_SPACE(*str))
		str++;
	if (*str)
		res = 0;
	board->num = res;
	free(src);
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

static int parse_room(char *str, )
{
	if (ft_strequ("##start", str))
		return (1);
	if (ft_strequ("##end", str))
		return (2);
	if (ft_strnequ("#", str, 1))
		return (3);

	return (0);
}

int read_rooms(int fd, t_board *board)
{
	char *str;
	t_room *room;

	while (get_next_line(fd, &str) > 0)
	{
		room = NULL;
		if (ft_strchr('-', str))
			break;

		ft_lstadd(&board->rooms, obj_in_lst(room));
		free(str);
	}
	return (0);
}

int read_connections(int fd, t_board *board)
{
	return (0);
}