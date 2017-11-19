/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_operations_addition.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:02:44 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/19 16:05:02 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_row	*push_row_begin(t_row **dest, unsigned int *columns, int size)
{
	t_row	*new;

	if (!dest)
		return (NULL);
	if (!(new = new_row(size)))
		return (NULL);
	if (columns)
		while (--size >= 0)
			new->columns[size] = columns[size];
	if (!*dest)
	{
		*dest = new;
		return (*dest);
	}
	new->next = (*dest)->next;
	new->prev = *dest;
	(*dest)->next->prev = new;
	(*dest)->next = new;
	return (*dest);
}
