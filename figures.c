/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:31:11 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/22 15:05:28 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	static int	calc_width(char matrix[4][4])
**
**	i is a row iterator
**
**	j is a col iterator
**
**	width_t is a temporary width of the figure
**
**	width is a final width of the figure
**
**	the function returns a calculated figure width in matrix[4][4]
*/

static int	calc_width(char matrix[4][4])
{
	int		i;
	int		j;
	int		width;

	width = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (matrix[j][i] == '#')
			{
				width++;
				break ;
			}
	}
	return (width);
}

/*
**	static int	calc_height(char matrix[4][4])
**
**	i is a row iterator
**
**	i_t is a temporary row iterator
**
**	j is a col iterator
**
**	height_t is a temporary figure height
**
**	height is a final figure height
**
**	the function returns a calculated figure height in matrix[4][4]
*/

static int	calc_height(char matrix[4][4])
{
	int		i;
	int		j;
	int		height;

	height = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (matrix[i][j] == '#')
			{
				height++;
				break ;
			}
	}
	return (height);
}

/*
**	t_figure	*new_figure(char name, char matrix[4][4])
**
**	new is an address of a new figure
**
**	i is a row iterator
**
**	j is a col iterator
**
**	the function allocates memmory for a new figure and sets its name,
**	size and matrix
*/

t_figure	*new_figure(char name, char matrix[4][4])
{
	t_figure	*new;
	int			i;
	int			j;

	if (!(new = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			new->matrix[i][j] = matrix[i][j];
	}
	new->name = name;
	fix_h_align(&new);
	fix_v_align(&new);
	new->width = calc_width(matrix);
	new->height = calc_height(matrix);
	new->next = NULL;
	return (new);
}

/*
**	t_figure	*new_figure(char name, char matrix[4][4])
**
**	new is an address of a new figure
**
**	the function pushes a new figure to the begining of **dest stack
*/

t_figure	*figure_push(t_figure **dest, char name, char matrix[4][4])
{
	int			i;
	int			j;
	t_bool		empty;
	t_figure	*new;

	if (!dest)
		return (NULL);
	empty = true;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (matrix[i][j] == '#')
				empty = false;
	}
	if (empty)
		matrix[0][0] = '#';
	new = new_figure(name, matrix);
	while (*dest)
		dest = &(*dest)->next;
	*dest = new;
	return (new);
}
