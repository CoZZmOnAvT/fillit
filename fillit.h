/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:22:27 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/15 18:21:06 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <string.h>
# include <stdlib.h>
#include <unistd.h>
# include <fcntl.h>

# define CHAR_BITS (sizeof(char) * 8)

/*
**	Typedefs
*/

typedef enum	e_bool
{
	false, true
}				t_bool;

typedef struct	s_row
{
	char			*columns;
	struct s_row	*down;
}				t_row;

typedef struct	s_figure
{
	char			name;
	char			matrix[4][4];
	unsigned char	width;
	unsigned char	height;
	struct s_figure	*next;
}				t_figure;

typedef struct	s_solution
{
	char			name;
	unsigned char	x;
	unsigned char	y;
	struct s_figure	*next;
}				t_solution;

/*
**	Global variables
*/

extern int			g_figure_count;

extern t_row		*g_basic_matrix;

extern t_row		*g_tmp_matrix;

extern t_figure		*figures;

extern t_solution	*b_sol;

extern t_solution	*t_sol;

/*
**	Prototypes
*/

char			get_bit_value(char string, unsigned char index);

void			set_bit_true(char *string, unsigned char index);

void			set_bit_false(char *string, unsigned char index);

char			get_figures(char *file_name);

void			figure_push(t_figure **dest, char name, char matrix[4][4]);

t_figure		*new_figure(char name, char matrix[4][4]);

#endif
