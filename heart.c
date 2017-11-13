/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:21:42 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/13 21:02:12 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fillit.h"
#include <stdio.h>

t_olist		*g_solutions;

t_object	*g_root;

int		main(int ac, char **av)
{
	t_object	*A;
	t_object	*A1;
	t_object	*A2;
	t_object	*B;
	t_object	*B1;
	t_object	*B2;
	t_object	*C;
	t_object	*C1;

	(void)av;
	if (ac != 2)
		return (write(2, "usage: ./fillit tetriminos_sample\n", 34));

	g_solutions = NULL;

	g_root = (t_object *)malloc(sizeof(t_object));
	g_root->x = 0;
	g_root->y = 0;
	g_root->name = 'R';
	g_root->size = 0;
	g_root->up = NULL;
	g_root->down = NULL;
	g_root->head = g_root;
	
	A = (t_object *)malloc(sizeof(t_object));
	A->x = 0;
	A->y = 0;
	A->name = 'A';
	A->size = 2;
	A->head = A;

	A1 = (t_object *)malloc(sizeof(t_object));
	A1->x = 1;
	A1->y = 2;
	A1->name = 0;
	A1->size = 0;
	A1->head = A;

	A2 = (t_object *)malloc(sizeof(t_object));
	A2->x = 1;
	A2->y = 3;
	A2->name = 0;
	A2->size = 0;
	A2->head = A;

	B = (t_object *)malloc(sizeof(t_object));
	B->x = 0;
	B->y = 0;
	B->name = 'B';
	B->size = 2;
	B->head = B;

	B1 = (t_object *)malloc(sizeof(t_object));
	B1->x = 1;
	B1->y = 1;
	B1->name = 0;
	B1->size = 0;
	B1->head = B;

	B2 = (t_object *)malloc(sizeof(t_object));
	B2->x = 1;
	B2->y = 3;
	B2->name = 0;
	B2->size = 0;
	B2->head = B;

	C = (t_object *)malloc(sizeof(t_object));
	C->x = 0;
	C->y = 0;
	C->name = 'C';
	C->size = 1;
	C->head = C;

	C1 = (t_object *)malloc(sizeof(t_object));
	C1->x = 1;
	C1->y = 1;
	C1->name = 0;
	C1->size = 0;
	C1->head = C;


	g_root->right = A;
	A->right = B;
	B->right = C;
	C->right = g_root;
	g_root->left = C;
	C->left = B;
	B->left = A;
	A->left = g_root;

	A->down = A1;
	A1->down = A2;
	A2->down = A;
	A->up = A2;
	A2->up = A1;
	A1->up = A;

	B->down = B1;
	B1->down = B2;
	B2->down = B;
	B->up = B2;
	B2->up = B1;
	B1->up = B;

	C->down = C1;
	C1->down = C;
	C->up = C1;
	C1->up = C;

	B1->right = C1;
	C1->right = B1;
	B1->left = C1;
	C1->left = B1;

	A2->right = B2;
	B2->right = A2;
	A2->left = B2;
	B2->left = A2;

	A1->left = A1;
	A1->right = A1;

	ft_search_x(0);

	return (0);
}
