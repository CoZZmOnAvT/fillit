/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/19 14:00:51 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int			g_figure_count = 0;

int			g_square_size = 0;

t_row		*g_basic_matrix = NULL;

t_figure	*g_figures = NULL;

t_row		*g_t_sol = NULL;

t_row		*g_b_sol = NULL;

int		main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (write(1, "usage: ./fillit [tetriminos_sample]\n", 36));
	if (!get_figures(av[1]))
		return (write(1, "error\n", 6));
	g_square_size = get_biggest_sqrt(g_figure_count * 4);
	push_row(&g_basic_matrix, NULL, 1);
	push_row(&g_t_sol, NULL, 1);
	while (true)
	{

		fill_basic_matrix();
		// print_figures();
		// debug_print(g_basic_matrix);
		ft_solve();
		// print_result();
		g_square_size++;
	}
	return (0);
}
