/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:33:16 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/21 16:18:35 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"

int			ft_draw(char (*output)[g_square_size][g_square_size])
{
	int		i;
	int		j;

	i = -0x1;
	while (++i < g_square_size)
	{
		j = -0x1;
		while (++j < g_square_size)
			if ((*output)[i][j])
				ft_putchar((*output)[i][j]);
			else
				ft_putchar(0x2E);
		ft_putchar(0xA);
	}
	return (00);
}

void		clear_output(char (*output)[g_square_size][g_square_size])
{
	int		i;

	i = -0x1;
	while (++i < g_square_size)
		ft_bzero((*output)[i], g_square_size);
}

int			print_result(void)
{
	t_row	*tmp;
	int		sys[0x3];
	char	output[g_square_size][g_square_size];

	tmp = g_sol;
	clear_output(&output);
	while ((tmp = tmp->next) != g_sol)
	{
		sys[0x0] = -0x1;
		while (++sys[0x0] < g_figure_count)
			if (get_bit_value(tmp->columns[0x0], sys[0x0]))
			{
				sys[0x2] = 0x41 + sys[0x0];
				break ;
			}
		sys[0x0] = 0x0;
		while (++sys[0x0] <= g_square_size)
		{
			sys[0x1] = -0x1;
			while (++sys[0x1] < g_square_size)
				if (get_bit_value(tmp->columns[sys[0x0]], sys[0x1]))
					output[sys[0x0] - 0x1][sys[0x1]] = sys[0x2];
		}
	}
	return (ft_draw(&output));
}
