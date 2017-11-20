/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:22:27 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/20 18:34:24 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define CHAR_BITS (sizeof(char) * 8)

# define INT_BITS (sizeof(int) * 8)

/*
**	Typedefs
*/

typedef enum		e_bool
{
	false, true
}					t_bool;

typedef struct		s_row
{
	struct s_row	*prev;
	unsigned int	*columns;
	struct s_row	*next;
}					t_row;

typedef struct		s_figure
{
	char			name;
	char			matrix[4][4];
	unsigned char	width;
	unsigned char	height;
	struct s_figure	*next;
}					t_figure;

typedef struct		s_container
{
	struct s_container	*prev;
	t_row				*row;
	struct s_container	*next;
}					t_container;

/*
**	Global variables
*/

extern int			g_figure_count;

extern int			g_square_size;

extern t_row		*g_basic_matrix;

extern t_row		*g_tmp_matrix;

extern t_figure		*g_figures;

extern t_row		*g_sol;

/*
**	Prototypes
*/

unsigned char		get_bit_value(unsigned int string, char index);

void				set_bit_true(unsigned int *string, char index);

void				set_bit_false(unsigned int *string, char index);

t_bool				get_figures(char *file_name);

void				fix_h_align(t_figure **figure);

void				fix_v_align(t_figure **figure);

t_figure			*figure_push(t_figure **dest, char name, char matrix[4][4]);

t_figure			*new_figure(char name, char matrix[4][4]);

void				ft_solve(int k);

void				ft_calc_square(int k);

int					get_biggest_sqrt(int num);

void				fill_basic_matrix(void);

t_row				*new_row(int columns);

t_row				*push_row(t_row **dest, unsigned int *columns, int size);

t_row				*push_row_begin(t_row **dest, unsigned int *columns,
									int size);

void				pop_row(t_row **src);

t_container			*push_to_container(t_container **dest, t_row *data);

void				clear_matrix(t_row *src);

int					print_result(void);

#endif
