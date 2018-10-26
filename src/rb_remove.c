/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:31:50 by jkrause           #+#    #+#             */
/*   Updated: 2018/10/25 20:10:10 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_node			*rb_find_edge(t_node *q)
{
	t_node		*edgelord;

	edgelord = q->children[0];
	while (edgelord->children[1] != 0)
		edgelord = edgelord->children[1];
	return (edgelord);
}

void			rb_remove(t_node *q)
{
	t_node		*save;
	int			red;

	if (q->children[0] == 0 || q->children[1] == 0)
	{
		red = IS_RED(q) || IS_RED(CHILD(q, CHILD(q, 0) == 0));
		save = rb_swallow(q);
		if (!save && !g_root)
			return ;
		if (save->red == 2)
			red = 1;
	}
	else
	{
		save = rb_find_edge(q);
		q->value = save->value;
		red = IS_RED(save);
		save = rb_swallow(save);
	}
	(!red ? rb_fix_rebalance(save, (save->children[0] != 0))
		: (save->red = 0));
}

/*
** These functions help rebalance the tree after node removals.
** It returns a positive integer when the tree no longer
** needs to be rebalanced.
**
** TODO: Try 2 line if with SETBLKRED at line 79.
*/

int				rb_rebal(t_node **p, t_node **s, int dir)
{
	int				wasred;

	if ((*s)->red == 0 && CBOTHBLK((*s)))
	{
		(*s)->red = 1;
		if ((*p)->red == 1)
			return (((*p)->red = 0) ? 1 : 1);
		return ((*p)->parent == 0 ? 1 : 0);
	}
	if (!IS_RED((*s)->children[!dir]))
	{
		(*s)->red = 1;
		*s = rb_rotate(*s, !dir);
		(*s)->red = 0;
	}
	wasred = IS_RED((*p));
	*p = rb_rotate(*p, dir);
	*s = ((*p)->children[!dir]);
	(*s)->red = 0;
	if (wasred)
	{
		(*p)->red = 1;
		(*p)->children[dir]->red = 0;
	}
	return (1);
}

void			rb_fix_rebalance(t_node *n, int dir)
{
	t_node		*p;
	t_node		*s;

	if (!n || (n == g_root && CB0(n)))
		return ;
	p = n;
	while (p)
	{
		s = p->children[!dir];
		if (IS_RED(s))
		{
			s = rb_rotate(p, dir);
			SETBLKRED(s, p);
			continue;
		}
		if (rb_rebal(&p, &s, dir) == 1)
			return ;
		dir = DIR(p);
		p = p->parent;
	}
}
