/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:41:30 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/21 16:19:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

t_row	*new_row(int columns)
{
	t_row	*new;

	if (!(new = (t_row *)malloc(sizeof(t_row))))
		return (NULL);
	if (!(new->columns = (unsigned int *)ft_memalloc(columns * sizeof(int))))
		return (NULL);
	new->next = new;
	new->prev = new;
	return (new);
}

t_row	*push_row(t_row **dest, unsigned int *columns, int size)
{
	t_row	*new;

	if (!dest)
		return (NULL);
	if (!(new = new_row(size)))
		return (NULL);
	if (columns)
		while (--size >= 0x0)
			new->columns[size] = columns[size];
	if (!*dest)
	{
		*dest = new;
		return (*dest);
	}
	(*dest)->prev->next = new;
	new->prev = (*dest)->prev;
	(*dest)->prev = new;
	new->next = *dest;
	return (*dest);
}

void	pop_row(t_row **src)
{
	t_row	*buff;

	(*src)->prev->prev->next = *src;
	buff = (*src)->prev;
	(*src)->prev = (*src)->prev->prev;
	free(buff->columns);
	free(buff);
}
