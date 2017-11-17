/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:45:54 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/04 13:46:50 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strnlen(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (s[len] && (unsigned char)s[len] != (unsigned char)c)
		len++;
	return (len);
}
