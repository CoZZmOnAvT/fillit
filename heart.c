/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/19 20:19:36 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int			g_figure_count = 0;

int			g_square_size = 0;

t_row		*g_basic_matrix = NULL;

t_figure	*g_figures = NULL;

t_row		*g_sol = NULL;

/*
**void	debug_print(t_row *row)
**{
**	t_row		**tmp;
**
**	tmp = &row;
**	while (*(tmp = &(*tmp)->next) != row)
**	{
**		for (int i = 0; i < g_figure_count; ++i)
**			printf("%d ", get_bit_value((*tmp)->columns[0], i));
**		for (int i = 1; i <= g_square_size; ++i)
**			for (int j = 0; j < g_square_size; ++j)
**				printf("%d ", get_bit_value((*tmp)->columns[i], j));
**		printf("\n");
**	}
**	printf("\n\n");
**}
*/

int		main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (write(1, "usage: ./fillit [tetriminos_sample]\n", 36));
	if (!get_figures(av[1]))
		return (write(1, "error\n", 6));
	g_square_size = get_biggest_sqrt(g_figure_count * 4);
	push_row(&g_basic_matrix, NULL, 1);
	push_row(&g_sol, NULL, 1);
	while (g_square_size < 16)
	{
		fill_basic_matrix();
		ft_solve();
		ft_rev_solve();
		clear_matrix(g_basic_matrix);
		g_square_size++;
	}
	return (0);
}
