/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:37:43 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/21 15:45:17 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

static t_container	*ft_new_container(t_row *data)
{
	t_container	*new;

	if (!(new = (t_container *)malloc(sizeof(t_container))))
		return (NULL);
	new->row = data;
	new->next = new;
	new->prev = new;
	return (new);
}

t_container			*push_to_container(t_container **dest, t_row *data)
{
	t_container	*new;

	if (!dest)
		return (NULL);
	if (!(new = ft_new_container(data)))
		return (NULL);
	if (!*dest)
		return ((*dest = new));
	(*dest)->next->prev = new;
	new->next = (*dest)->next;
	new->prev = *dest;
	(*dest)->next = new;
	return (*dest);
}
