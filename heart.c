/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/15 15:01:34 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fillit.h"
#include <stdio.h>

int			g_figure_count = 0;

t_row		*g_basic_matrix = NULL;

t_row		*g_tmp_matrix = NULL;

t_figures	*figures = NULL;

t_solution	*b_sol = NULL;

t_solution	*t_sol = NULL;

int		main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		return (write(2, "usage: ./fillit tetriminos_sample\n", 34));

	
}
