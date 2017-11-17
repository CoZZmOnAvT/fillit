/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:10:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/17 11:34:13 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

/*
**	static void		fix_h_align(t_figure **figure)
**
**	i is row iterator
**
**	i is col iterator
**
**	buff[4] is temporaty buffer for matrix one dimension
**
**	empty is variable wich show when row is empty
**
**	Function moves figure in figure->matrix maximum upper
*/

static void		fix_h_align(t_figure **figure)
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
**	i is row iterator
**
**	i is col iterator
**
**	buff is temporaty buffer for one symbol
**
**	empty is variable wich show when row is empty
**
**	Function moves figure in figure->matrix maximum left
*/

static void		fix_v_align(t_figure **figure)
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
**	i is row iterator
**
**	j is col iterator
**
**	blocks is counter that whows how many blocks in figure, should be 4
**
**	Function returns FALSE if figure brocken, TRUE otherwise
*/

static t_bool	validate_figure(t_figure *figure)
{
	int		i;
	int		j;
	int		blocks;

	blocks = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (figure->matrix[i][j] == '#')
			{
				if (blocks++ > 4)
					return (false);
				if ((i - 1 >= 0 && figure->matrix[i - 1][j] == '#')
					|| (i + 1 < 4 && figure->matrix[i + 1][j] == '#')
					|| (j - 1 >= 0 && figure->matrix[i][j - 1] == '#')
					|| (j + 1 < 4 && figure->matrix[i][j + 1] == '#'))
					continue ;
				return (false);
			}
	}
	fix_h_align(&figure);
	fix_v_align(&figure);
	return (blocks == 4 ? true : false);
}

/*
**	t_bool	read_row(int fd, int row, char *symb, char (*tmp)[4][4])
**
**	fd is file_descriptor
**
**	row is current_row_in_figure
**
**	*symb is address of symbol readed in get_figures function by system call
**
**	(*tmp)[4][4] is address of temporary matrix for each figure
**
**	col is current_col_in_figure
**
**	Function returns FALSE when error occurred, TRUE otherwise
*/

static t_bool	read_row(int fd, int row, char *symb, char (*tmp)[4][4])
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
	if (*symb != '\n')
		return (false);
	return (true);
}

/*
**	t_bool	get_figures(char *file_name)
**
**	sys is system variable that means:
**		sys[0] = file_descriptor;
**		sys[1] = current_row_in_figure;
**		sys[2] = end_of_file reached when 0
**		sys[3] = name_of_figure
**
**	tmp is temporary matrix for each figure
**
**	symb is symbol readed from Read system call
**
**	Function returns FALSE when error occurred, TRUE otherwise
*/

t_bool			get_figures(char *file_name)
{
	char	tmp[4][4];
	int		sys[4];
	char	symb;

	if ((sys[0] = open(file_name, O_RDONLY)) == -1)
		return (0);
	sys[1] = 0;
	sys[2] = 1;
	sys[3] = 'A';
	while (read(sys[0], &symb, 1) || !sys[2])
	{
		if (read_row(sys[0], sys[1], &symb, &tmp) == false)
			return (false);
		if (sys[1] == 3)
		{
			sys[1] = 0;
			figure_push(&g_figures, sys[3] + g_figure_count++, tmp);
			if (((sys[2] = !read(sys[0], &symb, 1)) && symb != '\n')
				|| validate_figure(g_figures) == false)
				return (false);
		}
		else
			sys[1]++;
	}
	return (symb != 0 ? true : false);
}
