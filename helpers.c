/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:58:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/17 18:19:14 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include <stdio.h>

void	debug_print(void)
{
	t_row	*tmp_r;
	int		i;
	int		j;

	tmp_r = g_basic_matrix;
	while (tmp_r)
	{
		i = -1;
		while (++i < g_figure_count)
			printf("%d ", get_bit_value(tmp_r->columns[0], i));
		i = 0;
		while (++i <= g_square_size)
		{
			j = -1;
			while (++j < g_square_size)
				printf("%d ", get_bit_value(tmp_r->columns[i], j));			
		}
		printf("\n");
		tmp_r = tmp_r->next;
	}
	printf("\n\n");
}

int			get_biggest_sqrt(int num)
{
	int		tmp;

	tmp = -1;
	while (++tmp <= num)
		if (tmp * tmp >= num)
			break ;
	return (tmp);
}

static void	calc_square_size(void)
{
	t_figure	*tmp;
	int			square_size;

	square_size = g_figure_count * 4;
	tmp = g_figures;
	while (tmp)
	{
		square_size += ABS((tmp->height - tmp->width));
		tmp = tmp->next;
	}
	g_square_size = get_biggest_sqrt(square_size);
}

void		fill_poss_positions(t_figure *figure, int h, int w)
{
	int		i;
	int		j;

	i = -1;
	while (++i < figure->height)
	{
		j = -1;
		while (++j < figure->width)
			if (figure->matrix[i][j] == '#')
				set_bit_true(&g_basic_matrix->columns[i + h + 1], j + w);
	}
}

void		fill_basic_matrix(void)
{
	int			d_limits[2];
	int			d[2];
	t_figure	*tmp;

	calc_square_size();
	tmp = g_figures;	
	while (tmp)
	{
		d_limits[0] = g_square_size - tmp->height + 1;
		d_limits[1] = g_square_size - tmp->width + 1;		
		d[0] = -1;		
		while (++d[0] < d_limits[0])
		{
			d[1] = -1;
			while (++d[1] < d_limits[1])
			{
				push_row(&g_basic_matrix, 1 + g_square_size);
				set_bit_true(&g_basic_matrix->columns[0], tmp->name - 'A');
				fill_poss_positions(tmp, d[0], d[1]);
			}
		}
		tmp = tmp->next;
	}
	debug_print();
}
