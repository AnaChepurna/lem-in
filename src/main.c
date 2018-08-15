#include "../lem_in.h"

static int	process(void)
{
	t_board		*board;
	int			error;

	error = 0;
	if ((board = (t_board *)malloc(sizeof(t_board))))
	{
		if (!read_ants(0, board))
			error = 1;
		read_rooms(0, board);
		print_rooms(board);
	}
	else
		error = 1;
	return (error);
}

int			main(int c, char **v)
{
	(void)c;
	(void)v;
	if (process())
		ft_putendl(RED "ERROR" RESET);
	return (0);
}