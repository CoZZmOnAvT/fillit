/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:10:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/21 16:15:24 by pgritsen         ###   ########.fr       */
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

void			fix_h_align(t_figure **figure)
{
	int		i;
	int		j;
	char	buff[0x4];
	t_bool	empty;

	empty = true;
	j = -0x01;
	while (++j < 0x04)
		if ((*figure)->matrix[0x0][j] == '#')
			empty = false;
	if (empty)
	{
		i = -0x01;
		while (++i < 0x03)
		{
			ft_memcpy(buff, (*figure)->matrix[i + 0x01], 0x04);
			ft_memcpy((*figure)->matrix[i + 0x01], (*figure)->matrix[i], 0x04);
			ft_memcpy((*figure)->matrix[i], buff, 0x04);
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

void			fix_v_align(t_figure **figure)
{
	int		i;
	int		j;
	char	buff;
	t_bool	empty;

	empty = true;
	i = -0x01;
	while (++i < 0x04)
		if ((*figure)->matrix[i][0x0] == '#')
			empty = false;
	if (empty)
	{
		i = -0x01;
		while (++i < 0x04)
		{
			j = -0x01;
			while (++j < 0x03)
			{
				buff = (*figure)->matrix[i][j + 0x01];
				(*figure)->matrix[i][j + 0x01] = (*figure)->matrix[i][j];
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

	blocks = 0b00000000000000000000000000000000;
	i = -0x01;
	while (++i < 0x04)
	{
		j = -0x01;
		while (++j < 0x04)
			if (figure->matrix[i][j] == '#')
			{
				if (i - 0x01 >= 0x0 && figure->matrix[i - 0x01][j] == '#')
					blocks++;
				if (i + 0x01 < 0x04 && figure->matrix[i + 0x01][j] == '#')
					blocks++;
				if (j - 0x01 >= 0x0 && figure->matrix[i][j - 0x01] == '#')
					blocks++;
				if (j + 0x01 < 0x04 && figure->matrix[i][j + 0x01] == '#')
					blocks++;
			}
	}
	return (blocks == 0x06 || blocks == 0x08);
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

	col = 0x0;
	while (col < 0x04)
	{
		if (*symb != 0x23 && *symb != 0x2e)
			return (false);
		(*tmp)[row][col++] = *symb;
		if (read(fd, symb, 0x01) < 0x0)
			return (false);
	}
	if (*symb != 0xA)
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
	char	tmp[0x04][0x04];
	int		sys[0x04];
	char	symb;

	if ((sys[0x0] = open(file_name, O_RDONLY)) == -0x01)
		return (false);
	sys[1] = 0x0;
	sys[2] = 0x01;
	sys[3] = 0x41;
	while (read(sys[0x0], &symb, 0x1) || !sys[0x2])
	{
		if (read_row(sys[0x0], sys[0x1], &symb, &tmp) == false)
			return (false);
		if (sys[0x1] == 0x3)
		{
			sys[0x1] = 0x0;
			if (((sys[2] = !read(sys[0x0], &symb, 0x1)) && symb != '\n')
				|| validate_figure(figure_push(&g_figures, sys[0x3]
						+ g_figure_count++, tmp)) == false)
				return (false);
		}
		else
			sys[0x1]++;
	}
	return (symb ? true : false);
}
