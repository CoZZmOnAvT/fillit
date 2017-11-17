/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:31:11 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/16 14:14:37 by pgritsen         ###   ########.fr       */
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
	int		width_t;
	int		width;

	width = 0;
	width_t = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (matrix[i][j] == '#')
				while (matrix[i][j++] == '#')
					width_t++;
		}
		if (width_t > width)
			width = width_t;
		width_t = 0;
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
	int		i_t;
	int		j;
	int		height_t;
	int		height;

	height = 0;
	height_t = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			i_t = i;
			if (matrix[i_t][j] == '#')
				while (matrix[i_t++][j] == '#')
					height_t++;
			if (height_t > height)
				height = height_t;
			height_t = 0;
		}
	}
	return (height);
}

/*
**	static void	calc_figure_size(t_figure *figure)
**
**	Function sets width and height for figure
*/

static void	calc_figure_size(t_figure *figure)
{
	figure->width = calc_width(figure->matrix);
	figure->height = calc_height(figure->matrix);
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
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			new->matrix[i][j] = matrix[i][j];
	}
	new->name = name;
	calc_figure_size(new);
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

void		figure_push(t_figure **dest, char name, char matrix[4][4])
{
	t_figure	*new;

	if (!dest)
		return ;
	new = new_figure(name, matrix);
	new->next = *dest;
	*dest = new;
}
