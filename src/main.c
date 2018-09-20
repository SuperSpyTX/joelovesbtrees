/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 11:43:55 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/20 15:34:15 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"
#include <stdlib.h>
#define RUN_ASSINSERT 1
#define RUN_LARGEINSERT 0
#define RUN_VIZDEBUG 0
#define RUN_NEGATIVES 1

/*
** exclude file: @norminette
*/

int				g_count;
int				disabled;

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
	if (!root || (w != -12 && disabled))
		return ;
	if (w > 0)
		ft_printf("Assert value is %d\n", w);
	rc = (CHILD(root, 1) == 0 ? -1 : CHILD(root, 1)->value);
	lc = (CHILD(root, 0) == 0 ? -1 : CHILD(root, 0)->value);
	lr = arr[(CHILD(root, 0) == 0 ? 2 : CHILD(root, 0)->red)];
	rr = arr[(CHILD(root, 1) == 0 ? 2 : CHILD(root, 1)->red)];
	if (g_root == root)
		dprintf(2, "(ROOT) ");
	else if (lr == 'N' && rr == 'N')
		return ;
	dprintf(2, "%d,%c --> (L) %d,%c --> (R) %d,%c --> (P) %d,%c (%d)|\n",
			root->value, (root->red == 1 ? 'R' : 'B'),
			lc, lr, rc, rr, (P(root) == 0 ? -1 : P(root)->value),
			(arr[(P(root) == 0 ? 2 : P(root)->red)]),
			(root->parent ? GETCHILD(root) : -1));
	print_buds(root->children[0], w);
	print_buds(root->children[1], w);
}

void			init_test(int first)
{
	g_root = rb_insert(g_root, first);
	g_root->red = 0;
}

void			insert_test(int data)
{
	rb_insert(g_root, data);
	ft_printf("Post insert: \n");
	if (!RUN_VIZDEBUG)
		print_buds(g_root, -1);
	if (RUN_ASSINSERT == 1)
		ft_printf("Assert: %d\n", rb_assert(g_root));
}

/*
** @exclude: norminette
*/

void			tests(char **argv, int argc)
{
	t_node		*n;
	int			i;
	int			max;

	max = (getenv("DELETE_SIZE") ? ft_atoi(getenv("DELETE_SIZE")) : 0);
	(max != 0 ? ft_printf("Really silly removal test incoming...\n") : (void)0);
	i = (max < 0 ? (max * -1) : 0);
	max = (max < 0 ? (max * -1) + 1 : max);
	for (; i < max; i++)
	{
		if (!g_root || CB0(g_root))
		{
			// Oh dear.
			ft_printf("Not enough nodes to be monika'd! Returning.\n");
			return ;
		}
		if (i + 1 < argc && (n = rb_search(g_root, ft_atoi(argv[i + 1]))))
		{
			ft_printf("Found node %d, removing.\n\n", i);
			rb_remove(n);
		}
		/*
		if ((n = rb_search(g_root, i * -1)))
		{
			ft_printf("Found n node %d, removing.\n\n", i * -1);
			rb_remove(n);
		}*/
		if (g_root)
		{
			ft_printf("Post removal: \n");
			print_buds(g_root, -1);
			if (RUN_ASSINSERT == 1)
				ft_printf("Assert: %d\n", rb_assert(g_root));
		}
	}
	if (!g_root)
		ft_printf("All nodes removed!\n");
}

void			debug(char **argv, int argc)
{
	int			cur;

	ft_printf("Args: ");
	cur = 0;
	while (++cur < argc)
	{
		if (cur != (argc - 1))
			ft_printf("%s,", argv[cur]);
		else
			ft_printf("%s\n", argv[cur]);
	}
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
	//disabled = (argc > 100 && !RUN_VIZDEBUG);
		disabled = (getenv("VIZDEBUG") ? 1 : 0);
	init_test(ft_atoi(argv[1]));
	//print_buds(g_root, -1);
	cur = 1;
	while (++cur < argc)
	{
		ft_printf("Inserting %c...\n\n", argv[cur][0]);
		insert_test(ft_atoi(argv[cur]));
	}
	/*if (RUN_VIZDEBUG)
	  print_buds(g_root, -1);
	  else
	  {
	  if (RUN_LARGEINSERT == 1)
	  ft_printf("Large Assert: %d\n", rb_assert(g_root));
	  ft_printf("**** Testing complete\n");
	  }*/
	tests(argv, argc);
	if (disabled)
		print_buds(g_root, -12);
	/*if (g_root)
	  {
	  AB("There are still nodes in the tree.  If this is not intentional, then the test has failed.");
	  }*/
	//	debug(argv, argc);
	ft_printf("**** Testing complete\n");
}
