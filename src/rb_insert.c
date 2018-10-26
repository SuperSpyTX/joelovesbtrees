/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:51:24 by jkrause           #+#    #+#             */
/*   Updated: 2018/10/25 19:56:20 by jkrause          ###   ########.fr       */
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

	if (!n)
		return ;
	q = n;
	while (q && IS_RED(q->parent) && IS_RED(q))
	{
		p = q->parent;
		g = p->parent;
		if (IS_RED(CHILD(g, !DIR(p))))
		{
			rb_invert(g);
			q = g;
			continue ;
		}
		else
		{
			if (DIR(q) != DIR(p))
				rb_rotate(p, !DIR(q));
			SETBLKRED(rb_rotate(g, !DIR(p)), g);
			break ;
		}
	}
}
