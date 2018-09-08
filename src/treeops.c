/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:51:24 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/08 10:59:20 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

void			rb_invert(t_node *n)
{
	n->red = !n->red;
	(n->children[0] ? n->children[0]->red = !n->red : (void)n);
	(n->children[1] ? n->children[1]->red = !n->red : (void)n);
	g_root->red = 0;
}

t_node			*rb_insert(t_node *root, int value, int dummy)
{
	t_node		*cur;

	cur = root;
	(void)dummy;
	while (cur)
	{
		/*if (IS_RED(CHILD(cur, 0)) == 1 && IS_RED(CHILD(cur, 1)) == 1)
			rb_invert(cur);
		if (IS_RED(P(cur)) && IS_RED(cur))
		{
			(GETCHILD(cur) != GETCHILD(P(cur)) ? rb_rotate(P(cur),
				GETCHILD(P(cur)), 0) : (void)0);
			rb_rotate(P(cur), GETCHILD(cur), 1);
		}*/
		if (cur->children[(cur->value < value)])
			cur = cur->children[(cur->value < value)];
		else
		{
			cur->children[(cur->value < value)] =
				rb_initialize(cur, value);
			cur = cur->children[(cur->value < value)];
			rb_fix_tree(cur);
			return (cur);
		}
	}
	return (rb_initialize(0, value));
}

/*
** Trying a fail safe solution to no saved children.
*/

t_node			*rb_rotate(t_node *q, int dir, int setcolors)
{
	t_node		*p;
	t_node		*odir;

	if (dir < 0 || dir > 1)
		abort();
	if (!q || (q->children[0] == 0 && q->children[1] == 0))
		return (0);
	ft_printf("Rotate at (%d, p: %d -> %d)\n", q->value, (q->parent ? q->parent->value : -1), dir);
	p = q->parent;
	odir = q->children[!dir];
	q->children[!dir] = odir->children[dir];
	if (odir->children[dir])
		odir->children[dir]->parent = q;
	odir->children[dir] = q;
	if (p)
		p->children[GETCHILD(q)] = odir;
	odir->parent = p;
	q->parent = odir;
	if (setcolors)
	{
		q->red = !q->red;
		odir->red = !q->red;
	}
	if (p == 0)
	{
		ft_printf("New root!\n");
		g_root = odir;
		g_root->red = 0;
	}
	return (odir);
}

/*
** TODO: move these to a different file.
** 8-14-18: Broken test cases:
** 1 5 2 4 3 3 2 4 5 1 (5)
**
** Case 2:
** 2 1 3 4 2 1 4 5 6 2 3 4 5 1 2 3 2 3 4 12 4 6 5436 5 4 36 54 36 5 4 3 453 54 325 4 325 4 32 5 43 25 43 25 43 25 4
** 3 25 43 25 4 325 4 32 5 43 2 3 4
*/

void			rb_fix_tree(t_node *q)
{
	t_node		*p;
	t_node		*g;

	if (!q)
		return ;
	p = q->parent;
	ft_printf("q: %d p: %d\n", q->value, (p ? p->value : 0));
	g = (p ? p->parent : 0);
	if (CBOTHRED(q) && q->red == 0)
	{
		rb_invert(q);
	}
	if (g && p && BOTHRED(q, p))
	{
		if (GETCHILD(q) != GETCHILD(p))
		{
			p = rb_rotate(p, !GETCHILD(q), 0);
		}
		return (rb_fix_tree(rb_rotate(g, !GETCHILD(p), 1)));
	}
	return (rb_fix_tree(q->parent));
}
