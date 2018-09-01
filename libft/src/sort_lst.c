/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:27:22 by achepurn          #+#    #+#             */
/*   Updated: 2018/09/01 16:27:24 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sort_lst1(t_list *start, t_list *lst,
	int (*f)(t_list *a, t_list *b))
{
	void	*content;

	if (!lst || !lst->next)
		return ;
	if ((*f)(lst, lst->next))
	{
		content = lst->content;
		lst->content = lst->next->content;
		lst->next->content = content;
		sort_lst1(start, start, f);
	}
	else
		sort_lst1(start, lst->next, f);
}

void		sort_lst(t_list *lst, int (*f)(t_list *a, t_list *b))
{
	sort_lst1(lst, lst, f);
}
