/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:41:30 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/17 18:20:42 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

static t_row	*new_row(int columns)
{
	t_row	*new;

	if (!(new = (t_row *)malloc(sizeof(t_row))))
		return (NULL);
	if (!(new->columns = (unsigned int *)ft_memalloc(columns * sizeof(int))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			push_row(t_row **dest, int columns)
{
	t_row	*new;

	if (!dest)
		return ;
	if (!(new = new_row(columns)))
		return ;
	if (*dest)
		(*dest)->prev = new;
	new->next = *dest;
	*dest = new;
}

void			add_row(t_row **dest, t_row *src)
{
	if (!dest)
		return ;
	if (*dest)
		(*dest)->prev = src;
	src->next = *dest;
	*dest = src;
}
