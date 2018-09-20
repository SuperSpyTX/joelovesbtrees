/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:51:24 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/19 14:23:46 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_node			*rb_insert(t_node *root, int value)
{
	t_node		*cur;

	cur = root;
	while (cur)
	{
		if (cur->children[(cur->value <= value)])
			cur = cur->children[(cur->value <= value)];
		else
		{
			cur->children[(cur->value <= value)] =
				rb_initialize(cur, value);
			cur = cur->children[(cur->value <= value)];
			if (cur->parent->red == 1)
				rb_fix_insert(cur);
			return (cur);
		}
	}
	return (rb_initialize(0, value));
}

/*
** "The Optimized Solution"
*/

void			rb_fix_insert(t_node *n)
{
	t_node		*p;
	t_node		*g;
	t_node		*q;
	char		t;

	if (!n)
		return ;
	q = n;
	t = 0;
	while (q)
	{
		p = q->parent;
		g = (p ? p->parent : 0);
		if (g && CBOTHRED(g))
			rb_invert(((t = 0)) ? g : g);
		if (p && BOTHRED(q, p))
		{
			if ((GETCHILD(q) != GETCHILD(p)))
				p = rb_rotate(p, !GETCHILD(q), 0);
			rb_rotate((g ? g : p), (!(t = 0) ? !GETCHILD(p) : -1), 1);
			break ;
		}
		q = p;
	}
}
