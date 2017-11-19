/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcorythm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:21:22 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/18 21:15:25 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void	ft_set_new_coords(int counter, int *saved_counter,
						int **it, int it_t[])
{
	if (*saved_counter == 2147483647)
		*it = (int *)malloc(sizeof(int) * 2);
	if (counter && counter < *saved_counter)
	{
		*saved_counter = counter;
		(*it)[0] = it_t[0];
		(*it)[1] = it_t[1];
	}
}

int		*ft_choose_column()
{
	t_row		**tmp_matrix;
	int			it_t[2];
	int			*it;
	int			counter;
	int			saved_counter;

	it_t[0] = 0;
	saved_counter = 2147483647;
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
			ft_set_new_coords(counter, &saved_counter, &it, it_t);
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
		{
			printf("! SOLUTION FOUND !\n\n");
			printf("SQURE SIZE - %d\n", g_square_size);
			t_row	*tmp;

			tmp = g_t_sol;
			while ((tmp = tmp->next) != g_t_sol)
			{
				for (int i = 0; i < g_figure_count; i++)
					printf("%d ", get_bit_value(tmp->columns[0], i));
				for (int i = 1; i <= g_square_size; i++)
					for (int j = 0; j < g_square_size; j++)
						printf("%d ", get_bit_value(tmp->columns[i], j));
				printf("\n");
			}
			exit(0);
		}
		g_f_i_s = 0;
		return ;
	}
	coords = ft_choose_column();
	tmp_matrix = &g_basic_matrix;
	while (*(tmp_matrix = &(*tmp_matrix)->next) != g_basic_matrix)
	{
		if (get_bit_value((*tmp_matrix)->columns[coords[0]], coords[1]))
		{
			coords[2]--;
			g_f_i_s++;
			push_row(&g_t_sol, (*tmp_matrix)->columns, 1 + g_square_size);
			ft_cover_row(*tmp_matrix, &g_tmp_matrix);
			ft_solve();
			ft_uncover_row(g_tmp_matrix);
			pop_row(&g_t_sol);
		}
	}
}
