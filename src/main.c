#include "../lem_in.h"

static int	process(t_board *board)
{
	int			error;

	error = 0;
	if (board)
	{
		if (!read_ants(0, board))
			error = 1;
		read_rooms(0, board);
		if (!(error = scout_start_end(board)))
		{
			board->start->order = 0;
			number_rooms(board->start);
			mark_roads(board->end);
			print_rooms(board->rooms);
			if (!board->end->commited)
				return (4);
			board->ants = get_colony(board->num, board->start);
			ft_putstr("\n");
			while (!step_colony(board->ants, board))
			{
				// printf("!!!!!!\n");
				sleep(1);
				ft_putstr("\n");
			}
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
	else if (error == 5)
		ft_putendl(RED "ERROR : memory problem" RESET);
	else if (error == 4)
		ft_putendl(RED "ERROR : there is no ways to end" RESET);
	else if (error == 6)
		ft_putendl(RED "ERROR : more than 1 start detected" RESET);
	else if (error == 7)
		ft_putendl(RED "ERROR : more than 1 end detected" RESET);
	else if (error == 8)
		ft_putendl(RED "ERROR : end not found" RESET);
	else if (error == 9)
		ft_putendl(RED "ERROR : start not found" RESET);
}

int			main(int c, char **v)
{
	t_board *board;

	(void)c;
	(void)v;
	board = new_board();
	print_error(process(board));
	clear_board(&board);
	return (0);
}