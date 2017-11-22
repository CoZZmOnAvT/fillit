/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:17:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/22 15:03:36 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

/*
**	char	get_bit_value(int string, unsigned char index)
**
**	the function returns a bit with $index number in $string number
*/

unsigned char	get_bit_value(unsigned int string, char index)
{
	return ((string & (1 << index)) >> index);
}

/*
**	void	set_bit_true(int *string, unsigned char index)
**
**	the function sets a bit with $index number in $string number to 1
*/

void			set_bit_true(unsigned int *string, char index)
{
	*string = (*string | (1 << index));
}
