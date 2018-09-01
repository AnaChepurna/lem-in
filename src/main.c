/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:53:56 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 13:53:58 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			number_rooms(board->start);
			mark_roads(board->end);
			board->ants = get_colony(board->num, board->start);
			ft_putstr("\n");
			if (!board->end->commited)
				return (4);
			while (!step_colony(board->ants, board))
				ft_putstr("\n");
			ft_putstr("\n");
		}
	}
	else
		error = 5;
	return (error);
}

static void	print_error(int error)
{
	if (error == 1)
		ft_putendl(RED "ERROR : ants not found" RESET);
	else if (error == 3)
		ft_putendl(YELLOW "\nWARNING! start and end is connected" RESET);
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

static int	start_connect_end(t_board *board)
{
	t_list	*lst;
	t_room	*room;
	int		res;
	t_ant	*ant;

	res = 0;
	lst = board->start->connect;
	while (lst)
	{
		room = lst->content;
		if (room->status == R_END)
			res = -1;
		lst = lst->next;
	}
	if (res == -1)
	{
		lst = board->ants;
		while (lst)
		{
			ant = lst->content;
			print_ant(ant, board->end);
			lst = lst->next; 
		}
	}
	return (res);
}

int			main(int c, char **v)
{
	t_board *board;
	int		error;

	(void)c;
	(void)v;
	board = new_board();
	error = process(board);
	if (error == 4)
		error += start_connect_end(board);
	print_error(error);
	clear_board(&board);
	return (0);
}

