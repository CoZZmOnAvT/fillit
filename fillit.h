/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:22:27 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/13 21:10:01 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <string.h>
# include <stdlib.h>

/*
**	Typedefs
*/

typedef enum	e_bool
{
	false, true
}				t_bool;

typedef struct	s_object
{
	unsigned char	x;
	unsigned char	y;
	unsigned char	name;
	long			size;
	struct s_object	*left;
	struct s_object	*right;
	struct s_object	*up;
	struct s_object	*down;
	struct s_object	*head;
}				t_object;

typedef struct	s_olist
{
	t_object		*figure;
	struct s_olist	*next;
}				t_olist;

/*
**	Global Variables
*/

extern t_olist	*g_solutions;

extern t_object	*g_root;

/*
**	Prototypes
*/


/*
**	O_LIST Functions
*/

void			ft_olst_push_object(t_olist *list, long index, t_object *obj);

void			ft_olst_pop_object(t_olist *list, long index);

t_olist			*ft_olst_index(t_olist *list, long index);

t_olist			*ft_olst_new(t_object *figure);

/*
**	Dancing links with Algorithm X Functions
*/

void			ft_search_x(long k);

#endif
