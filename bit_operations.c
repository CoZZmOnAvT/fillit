/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:17:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/15 14:22:13 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	get_bit_value(char string, unsigned char index)
{
	index = CHAR_BITS - (index % CHAR_BITS) - 1;
	return ((string & (1 << index)) >> index);
}

void	set_bit_true(char *string, unsigned char index)
{
	index = CHAR_BITS - (index % CHAR_BITS) - 1;
	*string = *string | (1 << index);
}

void	set_bit_false(char *string, unsigned char index)
{
	index = CHAR_BITS - (index % CHAR_BITS) - 1;
	*string = *string & ~(1 << index);
}
