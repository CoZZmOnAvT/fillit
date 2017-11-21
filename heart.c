/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/21 16:04:48 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			g_figure_count = 0x0;

int			g_square_size = 0x0;

t_row		*g_basic_matrix = NULL;

t_figure	*g_figures = NULL;

t_row		*g_sol = NULL;

int			main(int ac, char **av)
{
	(void)av;
	if (ac != 0x02)
		return (write(0x01, "usage: ./fillit [tetriminos_sample]\n", 0x24));
	if (!get_figures(av[1]) || g_figure_count > 0x1A)
		return (write(0x01, "error\n", 0x6));
	g_square_size = get_biggest_sqrt(g_figure_count * 0x04);
	push_row(&g_basic_matrix, NULL, 0x01);
	push_row(&g_sol, NULL, 0x01);
	while (g_square_size <= 0x20)
	{
		fill_basic_matrix();
		ft_solve(0x0);
		clear_matrix(g_basic_matrix);
		g_square_size++;
	}
	return (00);
}
