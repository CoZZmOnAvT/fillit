/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:10:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/22 17:47:06 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

/*
**	static void		fix_h_align(t_figure **figure)
**
**	i is a row iterator
**
**	j is a col iterator
**
**	buff[4] is a temporaty buffer for one-dimensional matrix
**
**	empty is a variable, which shows when the row is empty
**
**	the function moves a figure to the upper edge of a figure matrix
*/

void			fix_h_align(t_figure **figure)
{
	int		i;
	int		j;
	char	buff[4];
	t_bool	empty;

	empty = true;
	j = -1;
	while (++j < 4)
		if ((*figure)->matrix[0][j] == '#')
			empty = false;
	if (empty)
	{
		i = -1;
		while (++i < 3)
		{
			ft_memcpy(buff, (*figure)->matrix[i + 1], 4);
			ft_memcpy((*figure)->matrix[i + 1], (*figure)->matrix[i], 4);
			ft_memcpy((*figure)->matrix[i], buff, 4);
		}
		fix_h_align(figure);
	}
}

/*
**	static void		fix_v_align(t_figure **figure)
**
**	i is a row iterator
**
**	j is a col iterator
**
**	buff is a temporaty buffer for one symbol
**
**	empty is a variable, which shows when the row is empty
**
**	the function moves a figure to the left edge of a figure matrix
*/

void			fix_v_align(t_figure **figure)
{
	int		i;
	int		j;
	char	buff;
	t_bool	empty;

	empty = true;
	i = -1;
	while (++i < 4)
		if ((*figure)->matrix[i][0] == '#')
			empty = false;
	if (empty)
	{
		i = -1;
		while (++i < 4)
		{
			j = -1;
			while (++j < 3)
			{
				buff = (*figure)->matrix[i][j + 1];
				(*figure)->matrix[i][j + 1] = (*figure)->matrix[i][j];
				(*figure)->matrix[i][j] = buff;
			}
		}
		fix_v_align(figure);
	}
}

/*
**	t_bool	validate_figure(t_figure *figure)
**
**	i is a row iterator
**
**	j is a col iterator
**
**	blocks is a counter, which shows how many blocks are in the figure;
**	it should be equal to 4
**
**	the function returns FALSE if the figure is broken, TRUE otherwise
*/

static t_bool	validate_figure(t_figure *figure)
{
	int		i;
	int		j;
	int		conections;
	int		blocks;

	blocks = 0;
	conections = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (figure->matrix[i][j] == '#' && ++blocks)
			{
				if (i - 1 >= 0 && figure->matrix[i - 1][j] == '#')
					conections++;
				if (i + 1 < 4 && figure->matrix[i + 1][j] == '#')
					conections++;
				if (j - 1 >= 0 && figure->matrix[i][j - 1] == '#')
					conections++;
				if (j + 1 < 4 && figure->matrix[i][j + 1] == '#')
					conections++;
			}
	}
	return (blocks == 4 && (conections == 6 || conections == 8));
}

/*
**	t_bool	read_row(int fd, int row, char *symb, char (*tmp)[4][4])
**
**	fd is a file_descriptor
**
**	row is the current row in the figure
**
**	*symb is an address of a symbol read in get_figures function
**	during system call
**
**	(*tmp)[4][4] is an address of a temporary matrix created for each figure
**
**	col is the current column in the figure
**
**	the function returns FALSE if an error has occurred, TRUE otherwise
*/

static t_bool	read_row(int fd, int row, char *symb, char (*tmp)[4][4])
{
	int		col;

	col = 0;
	while (col < 4)
	{
		if (*symb != 35 && *symb != 46)
			return (false);
		(*tmp)[row][col++] = *symb;
		if (read(fd, symb, 1) < 0)
			return (false);
	}
	if (*symb != 10)
		return (false);
	return (true);
}

/*
**	t_bool	get_figures(char *file_name)
**
**	sys is a system variable, which means the following:
**		sys[0] = file_descriptor;
**		sys[1] = current_row_in_figure;
**		sys[2] = end_of_file reached when 0
**		sys[3] = name_of_figure
**
**	tmp is a temporary matrix for each figure
**
**	symb is a symbol read during read system call
**
**	the function returns FALSE if an error has occurred, TRUE otherwise
*/

t_bool			get_figures(char *file_name)
{
	char	tmp[4][4];
	int		sys[4];
	char	symb;

	if ((sys[0] = open(file_name, O_RDONLY)) == -1)
		return (false);
	sys[1] = 0;
	sys[2] = 1;
	sys[3] = 65;
	while (read(sys[0], &symb, 1) || !sys[2])
	{
		if (read_row(sys[0], sys[1], &symb, &tmp) == false)
			return (false);
		if (sys[1] == 3)
		{
			sys[1] = 0;
			if (((sys[2] = !read(sys[0], &symb, 1)) && symb != '\n')
				|| validate_figure(figure_push(&g_figures, sys[3]
						+ g_figure_count++, tmp)) == false)
				return (false);
		}
		else
			sys[1]++;
	}
	return (symb ? true : false);
}
