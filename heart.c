/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/20 18:52:11 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			g_figure_count = 0;

int			g_square_size = 0;

t_row		*g_basic_matrix = NULL;

t_figure	*g_figures = NULL;

t_row		*g_sol = NULL;

int			main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (write(1, "usage: ./fillit [tetriminos_sample]\n", 36));
	if (!get_figures(av[1]) || g_figure_count > 26)
		return (write(1, "error\n", 6));
	g_square_size = get_biggest_sqrt(g_figure_count * 4);
	push_row(&g_basic_matrix, NULL, 1);
	push_row(&g_sol, NULL, 1);
	while (g_square_size <= 32)
	{
		fill_basic_matrix();
		ft_solve(0);
		clear_matrix(g_basic_matrix);
		g_square_size++;
	}
	return (0);
}
