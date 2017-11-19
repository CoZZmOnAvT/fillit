/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcorythm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:21:22 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/19 20:26:19 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

int		*ft_choose_column(void)
{
	t_row		**tmp_matrix;
	int			it_t[2];
	int			*it;
	int			counter;

	it_t[0] = 0;
	it = (int *)malloc(sizeof(int) * 3);
	it[2] = 2147483647;
	while (++it_t[0] <= g_square_size)
	{
		it_t[1] = -1;
		while (++it_t[1] < g_square_size)
		{
			counter = 0;
			tmp_matrix = &g_basic_matrix;
			while (*(tmp_matrix = &(*tmp_matrix)->next) != g_basic_matrix)
				if (get_bit_value((*tmp_matrix)->columns[it_t[0]], it_t[1]))
					counter++;
			if (counter && it[2] > counter)
				ft_memcpy(it, (int[]){it_t[0], it_t[1], counter}, 12);
		}
	}
	return (it);
}

void	ft_cover_row(t_row *row, t_row **g_tmp_matrix)
{
	int		i;
	t_row	**tmp;
	t_row	*buff;

	tmp = &g_basic_matrix;
	while (*(tmp = &(*tmp)->next) != g_basic_matrix)
	{
		i = -1;
		while (++i < g_square_size + 1)
		{
			if ((row->columns[i] & (*tmp)->columns[i]) != 0)
			{
				buff = *tmp;
				(*tmp)->next->prev = (*tmp)->prev;
				(*tmp)->prev->next = (*tmp)->next;
				add_row(g_tmp_matrix, buff);
				tmp = &(*tmp)->prev;
				break ;
			}
		}
	}
}

void	ft_uncover_row(t_row *g_tmp_matrix)
{
	t_row	**tmp;
	t_row	*buff;

	tmp = &g_tmp_matrix;
	while (*(tmp = &(*tmp)->prev) != g_tmp_matrix)
	{
		buff = *tmp;
		(*tmp)->prev->next = (*tmp)->next;
		(*tmp)->next->prev = (*tmp)->prev;
		add_row_at_the_beginning(&g_basic_matrix, buff);
		tmp = &(*tmp)->next;
	}
}

int		g_f_i_s = 0;

void	ft_solve(void)
{
	int				*coords;
	t_row			**tmp_matrix;
	t_row			*g_tmp_matrix;

	g_tmp_matrix = NULL;
	push_row(&g_tmp_matrix, NULL, 1);
	if (g_basic_matrix == g_basic_matrix->next)
	{
		if (g_f_i_s == g_figure_count)
			exit(print_result());
		return (void)(g_f_i_s = 0);
	}
	coords = ft_choose_column();
	tmp_matrix = &g_basic_matrix;
	while (*(tmp_matrix = &(*tmp_matrix)->next) != g_basic_matrix)
		if (get_bit_value((*tmp_matrix)->columns[coords[0]], coords[1]))
		{
			g_f_i_s++;
			push_row(&g_sol, (*tmp_matrix)->columns, 1 + g_square_size);
			ft_cover_row(*tmp_matrix, &g_tmp_matrix);
			ft_solve();
			ft_uncover_row(g_tmp_matrix);
			pop_row(&g_sol);
		}
}

void	ft_rev_solve(void)
{
	int				*coords;
	t_row			**tmp_matrix;
	t_row			*g_tmp_matrix;

	g_tmp_matrix = NULL;
	push_row(&g_tmp_matrix, NULL, 1);
	if (g_basic_matrix == g_basic_matrix->next)
	{
		if (g_f_i_s == g_figure_count)
			exit(print_result());
		return (void)(g_f_i_s = 0);
	}
	coords = ft_choose_column();
	tmp_matrix = &g_basic_matrix;
	while (*(tmp_matrix = &(*tmp_matrix)->prev) != g_basic_matrix)
		if (get_bit_value((*tmp_matrix)->columns[coords[0]], coords[1]))
		{
			g_f_i_s++;
			push_row(&g_sol, (*tmp_matrix)->columns, 1 + g_square_size);
			ft_cover_row(*tmp_matrix, &g_tmp_matrix);
			ft_rev_solve();
			ft_uncover_row(g_tmp_matrix);
			pop_row(&g_sol);
		}
}
