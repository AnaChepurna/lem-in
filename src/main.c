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
		if (!(error = scout_start_end(board)))
		{
			board->start->order = 0;
			number_rooms(board->start);
			if (!(board->roads =  mark_roads(board->end)))
				return (3);
			board->ants = get_colony(board->num, board->start);
			while (!step_colony(board->ants, board))
				ft_putstr("\n");
			ft_putstr("\n");
		}
	}
	else
		error = 5;
	return (error);
}

static void print_error(int error)
{
	if (error == 1)
		ft_putendl(RED "ERROR : ants not found" RESET);
	else if (error == 2)
		ft_putendl(RED "ERROR : " RESET);
}

int			main(int c, char **v)
{
	(void)c;
	(void)v;
	print_error(process());
	return (0);
}