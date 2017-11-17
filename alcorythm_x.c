/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcorythm_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:21:22 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/17 19:39:06 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*					###Algorythm X###
If R[h] = h, print the current solution (see below) and return.
Otherwise choose a column object c (see below).
Cover column c (see below).
For each r ← D[c], D[D[c]] , . . . , while r 6= c,
	set Ok ← r;
	for each j ← R[r], R[R[r]] , . . . , while j 6= r,
		cover column j (see below);
	search(k + 1);
	set r ← Ok and c ← C[r];
	for each j ← L[r], L[L[r]] , . . . , while j 6= r,
		uncover column j (see below).
Uncover column c (see below) and return.
*/

t_row	*g_tmp_matrix = NULL;

void	ft_set_new_coords(int counter, int *saved_counter,
						int **it, int it_t[])
{
	if (*saved_counter == 2147483647)
		*it = (int *)malloc(sizeof(int) * 2);
	if (counter && counter < *saved_counter)
	{
		*saved_counter = counter;
		(*it)[0] = it_t[0];
		(*it)[1] = it_t[1];
	}
}

int		*ft_choose_column()
{
	t_row		*tmp_matrix;
	int			it_t[2];
	int			*it;
	int			counter;
	int			saved_counter;

	it_t[0] = 0;
	saved_counter = 2147483647;
	while (++it_t[0] <= g_square_size)
	{
		it_t[1] = -1;
		while (++it_t[1] < g_square_size)
		{
			counter = 0;	
			tmp_matrix = g_basic_matrix;
			while (tmp_matrix)
			{
				if (get_bit_value(tmp_matrix->columns[it_t[0]], it_t[1]))
					counter++;
				tmp_matrix = tmp_matrix->next;
			}
			ft_set_new_coords(counter, &saved_counter, &it, it_t);
		}
	}
	return (it);
}

void	ft_cover_row(t_row **row)
{
	int		i;
	t_row	**tmp;
	
	tmp = &g_basic_matrix;
	while (*tmp)
	{
		i = -1;
		while (++i < g_square_size + 1)
			if ((*row)->columns[i] & (*tmp)->columns[i])
			{
				printf("%u\n", (*tmp)->columns[i]);
				if ((*tmp)->prev)
					(*tmp)->prev->next = (*tmp)->next;
				else
					*tmp = (*tmp)->next;				
				if (*tmp && (*tmp)->next)
					(*tmp)->next->prev = (*tmp)->prev;
				else if (*tmp)
					*tmp = (*tmp)->prev;
				break ;
			}
		if ((*tmp))
			tmp = &(*tmp)->next;
	}
}

void	ft_uncover_row(t_row **row)
{
	(void)row;
}

void	ft_solve(void)
{
	int		*coords;
	t_row	**tmp_matrix;

	if (!g_basic_matrix)
	{
		printf("! SOLUTION FOUND !\n\n");
		return ;
	}
	coords = ft_choose_column();
	tmp_matrix = &g_basic_matrix;
	while (*tmp_matrix)
	{
		if (get_bit_value((*tmp_matrix)->columns[coords[0]], coords[1]))
			ft_cover_row(tmp_matrix);		
		// ft_solve();
		// if (get_bit_value(tmp_matrix->columns[coords[0]], coords[1]))
		// 	ft_uncover_row(tmp_matrix);
		if (*tmp_matrix)
			tmp_matrix = &(*tmp_matrix)->next;
		//printf("%p\n", g_basic_matrix->next);	
	}
}
