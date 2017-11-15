/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/15 19:02:23 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int			g_figure_count = 0;

t_row		*g_basic_matrix = NULL;

t_row		*g_tmp_matrix = NULL;

t_figure	*figures = NULL;

t_solution	*b_sol = NULL;

t_solution	*t_sol = NULL;

int		main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (write(1, "usage: ./fillit tetriminos_sample\n", 34));
	if (!get_figures(av[1]))
		return (write(1, "error\n", 6));
	while (figures)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (figures->matrix[i][j] == '#')
					printf("%c", figures->name);
				else
					printf("%c", figures->matrix[i][j]);
			}
			printf("\n");
		}
		printf("NAME - %c, HEIGHT - %d, WIDTH - %d\n\n", figures->name, figures->height, figures->width);
		figures = figures->next;
	}
	//solve();
	//print_result();
	return (0);
}
