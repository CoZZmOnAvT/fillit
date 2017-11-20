/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcorythm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:21:22 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/20 18:59:06 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

long	g_iterarions = 0;

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

void	ft_clear_rows(t_row *row, t_container **row_container)
{
	int		i;
	t_row	**tmp;

	tmp = &g_basic_matrix;
	while (*(tmp = &(*tmp)->next) != g_basic_matrix)
	{
		i = -1;
		while (++i < g_square_size + 1)
		{
			if ((row->columns[i] & (*tmp)->columns[i]) != 0)
			{
				push_to_container(row_container, *tmp);
				(*tmp)->next->prev = (*tmp)->prev;
				(*tmp)->prev->next = (*tmp)->next;
				tmp = &(*tmp)->prev;
				break ;
			}
		}
	}
}

void	ft_restore_rows(t_container *row_container, t_row *row)
{
	int			i;
	t_container	**tmp;
	t_container	*buff;

	tmp = &row_container;
	while (*(tmp = &(*tmp)->next) != row_container)
	{
		i = -1;
		while (++i < g_square_size + 1)
		{
			if ((row->columns[i] & (*tmp)->row->columns[i]) != 0)
			{
				buff = *tmp;
				(*tmp)->row->next->prev = (*tmp)->row;
				(*tmp)->row->prev->next = (*tmp)->row;
				(*tmp)->next->prev = (*tmp)->prev;
				(*tmp)->prev->next = (*tmp)->next;
				tmp = &(*tmp)->prev;
				free(buff);
				break ;
			}
		}
	}
}

void	ft_solve(int k)
{
	t_row		*buff;
	t_row		**tmp_matrix;
	t_container	*row_container;

	row_container = NULL;
	push_to_container(&row_container, NULL);
	if (g_basic_matrix == g_basic_matrix->next)
	{
		if (k == g_figure_count)
			exit(print_result());
		return ;
	}
	tmp_matrix = &g_basic_matrix;
	while (*(tmp_matrix = &(*tmp_matrix)->next) != g_basic_matrix
			&& get_bit_value((*tmp_matrix)->columns[0], k))
	{
		buff = *tmp_matrix;
		push_row(&g_sol, buff->columns, 1 + g_square_size);
		ft_clear_rows(buff, &row_container);
		ft_solve(k + 1);
		pop_row(&g_sol);
		ft_restore_rows(row_container, buff);
	}	
}
