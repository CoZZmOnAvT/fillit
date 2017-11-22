/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:58:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/22 13:39:47 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

void		clear_matrix(t_row *src)
{
	t_row		**tmp;
	t_row		*buff;

	tmp = &src->next;
	while (*tmp != src)
	{
		buff = (*tmp)->next;
		ft_bzero((*tmp)->columns, g_square_size + 1);
		free((*tmp)->columns);
		free(*tmp);
		*tmp = buff;
	}
	src->next = src;
	src->prev = src;
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
				set_bit_true(&g_basic_matrix->prev->columns[i + h + 1], j + w);
	}
}

void		fill_basic_matrix(void)
{
	int			d_limits[2];
	int			d[2];
	t_figure	*tmp;

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
				push_row(&g_basic_matrix, NULL, 1 + g_square_size);
				set_bit_true(&g_basic_matrix->prev->columns[0],
								tmp->name - 65);
				fill_poss_positions(tmp, d[0], d[1]);
			}
		}
		tmp = tmp->next;
	}
}
