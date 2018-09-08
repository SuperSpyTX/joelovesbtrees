/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 11:43:55 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/08 10:53:05 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"
#define RUN_ASSINSERT 1

/*
** This is a basic tester program.
*/

void			print_buds(t_node *root, int w)
{
	int			rc;
	int			lc;
	char		*arr;
	char		lr;
	char		rr;

	arr = "BRN";
	if (!root)
		return ;
	if (w != -1)
		ft_printf("Assert value is %d\n", w);
	rc = (CHILD(root, 1) == 0 ? -1 : CHILD(root, 1)->value);
	lc = (CHILD(root, 0) == 0 ? -1 : CHILD(root, 0)->value);
	lr = arr[(CHILD(root, 0) == 0 ? 2 : CHILD(root, 0)->red)];
	rr = arr[(CHILD(root, 1) == 0 ? 2 : CHILD(root, 1)->red)];
	if (g_root == root)
		ft_printf("(ROOT) ");
	else if (lr == 'N' && rr == 'N')
		return ;
	ft_printf("%d,%c --> (L) %d,%c --> (R) %d,%c --> (P) %d,%c (%d)|\n",
			root->value, (root->red == 1 ? 'R' : 'B'),
			lc, lr, rc, rr, (P(root) == 0 ? -1 : P(root)->value),
			(arr[(P(root) == 0 ? 2 : P(root)->red)]),
			(root->parent ? GETCHILD(root) : -1));
	print_buds(root->children[0], -1);
	print_buds(root->children[1], -1);
}

void			init_test(int first)
{
	g_root = rb_insert(g_root, first, 0);
	g_root->red = 0;
}

void			insert_test(int data)
{
	rb_insert(g_root, data, 0);
	ft_printf("Post rotations: \n");
	print_buds(g_root, -1);
	if (RUN_ASSINSERT == 1)
		print_buds(g_root, rb_assert(g_root));
	else
		print_buds(g_root, -1);
}

void			tests(void)
{
}

int				main(int argc, char **argv)
{
	int			cur;

	cur = 1;
	if (argc < 2)
	{
		ft_printf("Usage: %s [root] [node] (ex: 3 4 2 ...)", argv[0]);
		return (-1);
	}
	init_test(ft_atoi(argv[1]));
	print_buds(g_root, -1);
	while (++cur < argc)
	{
		ft_printf("Inserting %c...\n\n", argv[cur][0]);
		insert_test(ft_atoi(argv[cur]));
	}
	tests();
	ft_printf("**** Testing complete\n");
}
