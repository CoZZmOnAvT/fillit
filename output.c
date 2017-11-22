/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:33:16 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/22 13:32:58 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"

int			ft_draw(char (*output)[g_square_size][g_square_size])
{
	int		i;
	int		j;

	i = -1;
	while (++i < g_square_size)
	{
		j = -1;
		while (++j < g_square_size)
			if ((*output)[i][j])
				ft_putchar((*output)[i][j]);
			else
				ft_putchar(46);
		ft_putchar(10);
	}
	return (0);
}

void		clear_output(char (*output)[g_square_size][g_square_size])
{
	int		i;

	i = -1;
	while (++i < g_square_size)
		ft_bzero((*output)[i], g_square_size);
}

int			print_result(void)
{
	t_row	*tmp;
	int		sys[3];
	char	output[g_square_size][g_square_size];

	tmp = g_sol;
	clear_output(&output);
	while ((tmp = tmp->next) != g_sol)
	{
		sys[0] = -1;
		while (++sys[0] < g_figure_count)
			if (get_bit_value(tmp->columns[0], sys[0]))
			{
				sys[2] = 65 + sys[0];
				break ;
			}
		sys[0] = 0;
		while (++sys[0] <= g_square_size)
		{
			sys[1] = -1;
			while (++sys[1] < g_square_size)
				if (get_bit_value(tmp->columns[sys[0]], sys[1]))
					output[sys[0] - 1][sys[1]] = sys[2];
		}
	}
	return (ft_draw(&output));
}
