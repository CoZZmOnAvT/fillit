/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:10:22 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/08 20:27:36 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		ft_putnbr(int n)
{
	long int	mult;
	long int	n_t;

	mult = 1;
	n_t = n;
	if (n_t < 0)
	{
		ft_putchar('-');
		n_t *= -1;
	}
	if (n_t == 0)
		ft_putchar('0');
	while (n_t / mult != 0)
		mult *= 10;
	while (mult > 1)
	{
		mult /= 10;
		if (mult == 0)
			ft_putchar(n_t + '0');
		else
			ft_putchar(n_t / mult + '0');
		n_t %= mult;
	}
}
