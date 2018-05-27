#include "../lem_in.h"

static void	process(void)
{
	t_board		*board;

	if ((board = (t_board *)malloc(sizeof(t_board))))
	{#include "../lem_in.h"
		
		free(board);
	}
}

int			main(int c, char **v)
{
	(void)c;
	(void)v;
	process();
	return (0);
}