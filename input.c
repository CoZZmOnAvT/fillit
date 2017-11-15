/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:10:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/15 18:53:55 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int		read_row(int fd, int row, char *symb, char (*tmp)[4][4])
{
	int		col;

	col = 0;
	while (col < 4)
	{
		if (*symb != '#' && *symb != '.')
			return (0);
		(*tmp)[row][col++] = *symb;
		if (read(fd, symb, 1) < 0)
			return (0);
	}
	return (1);
}

char	get_figures(char *file_name)
{
	char	tmp[4][4];
	int		row;
	int		fd;
	char	symb;
	char	name;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	row = 0;
	name = 'A';
	while (read(fd, &symb, 1))
	{
		if (!read_row(fd, row, &symb, &tmp))
			return (0);
		if (row == 3)
		{
			row = 0;
			figure_push(&figures, name++, tmp);
			if (read(fd, &symb, 1) < 0 || symb != '\n')
				return (0);
		}
		else
			row++;
	}
	return (1);
}
