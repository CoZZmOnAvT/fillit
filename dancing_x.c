/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dancing_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:33:03 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/13 21:13:32 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>
#include <unistd.h>

t_object	*choose_column(void)
{
	t_object	*column;
	t_object	*j;
	long		size;

	size = 9223372036854775807;
	j = g_root;
	while ((j = j->right) != g_root)
		if (j->size < size)
		{
			column = j;
			size = j->size;
		}
	return (column);
}

/*
Set L[R[c]] ← L[c] and R[L[c]] ← R[c].
For each i ← D[c], D[D[c]] , . . . , while i != c,
	for each j ← R[i], R[R[i]] , . . . , while j != i,
		set U[D[j]] ← U[j], D[U[j]] ← D[j], and
		set S[C[j]] ← S[C[j]− 1
*/

void		ft_cover(t_object *column)
{
	t_object	*i;
	t_object	*j;

	column->right->left = column->left;
	column->left->right = column->right;
	i = column;	
	while ((i = i->down) != column)
	{
		sleep(1);
		j = i;
		while ((j = j->right) != i)
		{
			if (j == g_root)
				continue ;
			j->down->up = j->up;
			j->up->down = j->down;
			j->head->size = j->head->size - 1;
		}
	}
}

void		ft_uncover(t_object *column)
{
	t_object	*i;
	t_object	*j;

	i = column;
	while ((i = i->up) != column)
	{
		j = i;
		while ((j = j->left) != i)
		{
			j->head->size = j->head->size + 1;
			j->down->up = j;
			j->up->down = j;
		}
	}
	column->right->left = column;
	column->left->right = column;
}

void		ft_search_x(long k)
{
	t_object	*column;
	t_object	*r;
	t_object	*j;

	if (g_root->right == g_root)
		return ;
	column = choose_column();
	ft_cover(column);
	r = column;
	while ((r = r->down) != column)
	{
		ft_olst_push_object(g_solutions, k, r);		
		j = r;
		while ((j = j->right) != r)
			ft_cover(j);
		ft_search_x(k + 1);
		ft_olst_pop_object(g_solutions, k);
		column = r->head;
		j = r;
		while ((j = j->left) != r)
			ft_uncover(j);
		ft_uncover(column);
	}
}
