/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:53:44 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 13:53:47 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void			clear_ant(void *a, size_t size)
{
	(void)size;
	free(a);
}

t_list			*get_colony(int num, t_room *start)
{
	t_list	*lst;
	t_ant	*ant;
	int		i;

	lst = NULL;
	i = 0;
	while (++i <= num)
	{
		if ((ant = (t_ant *)malloc(sizeof(t_ant))))
		{
			ant->number = i;
			ant->location = start;
			ft_lstaddend(&lst, obj_in_lst((void *)ant));
		}
	}
	return (lst);
}

void			print_ant(t_ant *ant)
{
	ft_putstr("L");
	ft_putnbr(ant->number);
	ft_putstr("-");
	ft_putstr(ant->location->name);
	ft_putstr(" ");
}
