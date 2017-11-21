/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:58:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/21 16:19:48 by pgritsen         ###   ########.fr       */
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
		ft_bzero((*tmp)->columns, g_square_size + 0x01);
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

	tmp = -0x01;
	while (++tmp <= num)
		if (tmp * tmp >= num)
			break ;
	return (tmp);
}

void		fill_poss_positions(t_figure *figure, int h, int w)
{
	int		i;
	int		j;

	i = -0x01;
	while (++i < figure->height)
	{
		j = -0x01;
		while (++j < figure->width)
			if (figure->matrix[i][j] == '#')
				set_bit_true(&g_basic_matrix->prev->columns[i + h + 01], j + w);
	}
}

void		fill_basic_matrix(void)
{
	int			d_limits[0x02];
	int			d[0x02];
	t_figure	*tmp;

	tmp = g_figures;
	while (tmp)
	{
		d_limits[0x0] = g_square_size - tmp->height + 0x01;
		d_limits[0x1] = g_square_size - tmp->width + 0x01;
		d[0] = -0x01;
		while (++d[0x0] < d_limits[0x0])
		{
			d[0x1] = -0x1;
			while (++d[0x1] < d_limits[0x1])
			{
				push_row(&g_basic_matrix, NULL, 0x1 + g_square_size);
				set_bit_true(&g_basic_matrix->prev->columns[0],
								tmp->name - 0x41);
				fill_poss_positions(tmp, d[0x0], d[0x1]);
			}
		}
		tmp = tmp->next;
	}
}
