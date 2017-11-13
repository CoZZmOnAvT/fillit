/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_olist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:31:36 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/13 21:05:10 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_olist		*ft_olst_new(t_object *figure)
{
	t_olist	*new;

	new = (t_olist *)malloc(sizeof(t_olist));
	new->figure = figure;
	new->next = NULL;
	return (new);
}

t_olist		*ft_olst_index(t_olist *list, long index)
{
	while (list && index--)
		list = list->next;
	if (!list)
		list = ft_olst_new(NULL);
	return (list);
}

void		ft_olst_push_object(t_olist *list, long index, t_object *obj)
{
	list = ft_olst_index(list, index);
	if (!list)
		return ;
	if (!list->figure)
		list->figure = obj;
	else if (obj)
	{
		obj->right = list->figure;
		list->figure = obj;
	}
}

void		ft_olst_pop_object(t_olist *list, long index)
{
	list = ft_olst_index(list, index);
	if (!list)
		return ;
	if (list->figure)
		list->figure = list->figure->right;
}
