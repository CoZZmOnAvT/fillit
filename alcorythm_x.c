/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcorythm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:21:22 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/22 13:29:39 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

t_container	*g_row_container = NULL;

int		ft_clear_rows(t_row *row, t_container **row_container)
{
	int		i;
	int		count;
	t_row	**tmp;

	count = 0;
	tmp = &g_basic_matrix;
	while (*(tmp = &(*tmp)->next) != g_basic_matrix)
	{
		i = -1;
		while (++i < g_square_size + 1)
			if (row->columns[i] & (*tmp)->columns[i])
			{
				push_to_container(row_container, *tmp);
				(*tmp)->next->prev = (*tmp)->prev;
				(*tmp)->prev->next = (*tmp)->next;
				tmp = &(*tmp)->prev;
				count++;
				break ;
			}
	}
	return (count);
}

void	ft_restore_rows(t_container *row_container, int count)
{
	t_container	**tmp;
	t_container	*buff;

	tmp = &row_container;
	while (count-- && *(tmp = &(*tmp)->next) != row_container)
	{
		buff = *tmp;
		(*tmp)->row->next->prev = (*tmp)->row;
		(*tmp)->row->prev->next = (*tmp)->row;
		(*tmp)->next->prev = (*tmp)->prev;
		(*tmp)->prev->next = (*tmp)->next;
		tmp = &(*tmp)->prev;
		free(buff);
	}
}

void	ft_solve(int k)
{
	int			count;
	t_row		*buff;
	t_row		**tmp_matrix;

	if (g_basic_matrix == g_basic_matrix->next)
	{
		if (k == g_figure_count)
			exit(print_result());
		return ;
	}
	if (!g_row_container)
		push_to_container(&g_row_container, NULL);
	tmp_matrix = &g_basic_matrix;
	while (*(tmp_matrix = &(*tmp_matrix)->next) != g_basic_matrix
			&& get_bit_value((*tmp_matrix)->columns[0], k))
	{
		buff = *tmp_matrix;
		push_row(&g_sol, buff->columns, 1 + g_square_size);
		count = ft_clear_rows(buff, &g_row_container);
		ft_solve(k + 1);
		pop_row(&g_sol);
		ft_restore_rows(g_row_container, count);
	}
}
