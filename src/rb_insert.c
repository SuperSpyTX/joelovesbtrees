/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:51:24 by jkrause           #+#    #+#             */
/*   Updated: 2018/10/25 17:53:28 by jkrause          ###   ########.fr       */
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
			else
				ft_printf("No need to fix node.\n");
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

	if (!(q = n))
		return ;
	q = n;
	while (q && IS_RED(q->parent) && IS_RED(q))
	{
		ft_printf("Fixing insert on node %d\n", q->value);
		p = q->parent;
		g = p->parent;
		ft_printf("Autism Check: %d\n", IS_RED(CHILD(g, !DIR(p))));
		ft_printf("Autism Check Old: %d\n", CBOTHRED(g));
		if (IS_RED(CHILD(g, !DIR(p))))
		{
			ft_printf("Grandparent children are both red.  Inverting grandparent.\n");
			rb_invert(g);
			q = g;
			continue ;
		}
		else
		{
			ft_printf("Red violation at p %d & q %d\n", p->value, q->value);
			if (DIR(q) != DIR(p))
				rb_rotate(p, !DIR(q));
			//rb_rotate(g, !DIR(p));
			SETBLKRED(rb_rotate(g, !DIR(p)), g);
			break ;
		}
	}
}
