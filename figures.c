/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:31:11 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/21 16:01:33 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	static int	calc_width(char matrix[4][4])
**
**	i is row iterator
**
**	j is col iterator
**
**	width_t is temporary width of figure
**
**	width is finaly width of figure
**
**	Function returns calculated width of figure in matrix[4][4]
*/

static int	calc_width(char matrix[4][4])
{
	int		i;
	int		j;
	int		width;

	width = 0x0;
	i = -0x1;
	while (++i < 0x4)
	{
		j = -0x1;
		while (++j < 0x4)
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
**	i is row iterator
**
**	i_t is temporary row iterator
**
**	j is col iterator
**
**	height_t is temporary height of figure
**
**	height is finaly height of figure
**
**	Function returns calculated height of figure in matrix[4][4]
*/

static int	calc_height(char matrix[4][4])
{
	int		i;
	int		j;
	int		height;

	height = 0x0;
	i = -0x1;
	while (++i < 0x4)
	{
		j = -0x1;
		while (++j < 0x4)
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
**	new is an address of new figure
**
**	i is row iterator
**
**	j is col iterator
**
**	Function allocate memmory for new figure and sets her name, size and matrix
*/

t_figure	*new_figure(char name, char matrix[4][4])
{
	t_figure	*new;
	int			i;
	int			j;

	if (!(new = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	i = -0x1;
	while (++i < 0x4)
	{
		j = -0x1;
		while (++j < 0x4)
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
**	new is an address of new figure
**
**	Function push new figure at the begining of **dest stack
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
	i = -0x1;
	while (++i < 0x4)
	{
		j = -0x1;
		while (++j < 0x4)
			if (matrix[i][j] == '#')
				empty = false;
	}
	if (empty)
		matrix[0x0][0x0] = '#';
	new = new_figure(name, matrix);
	while (*dest)
		dest = &(*dest)->next;
	*dest = new;
	return (new);
}
