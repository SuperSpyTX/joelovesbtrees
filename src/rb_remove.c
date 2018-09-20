/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:31:50 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/20 15:52:59 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_node			*rb_find_edge(t_node *q, int *wasred)
{
	t_node		*edgelord;

	edgelord = q->children[0];
	while (edgelord->children[1] != 0)
		edgelord = edgelord->children[1];
	*wasred = (q->children[0]->red == 1);
	return (edgelord);
}

void			rb_remove(t_node *q)
{
	t_node		*save;
	int			wasred;

	if (q->children[0] == (void*)(intmax_t)(wasred = 0) || q->children[1] == 0)
	{
		if (CHILD(q, CHILD(q, 0) == 0) != 0)
			wasred = IS_RED(CHILD(q, CHILD(q, 0) == 0));
		save = rb_swallow(q);
		if (!save && !g_root)
			return ;
		wasred = (save->red > 1);
	}
	else
	{
		save = rb_find_edge(q, &wasred);
		q->value = save->value;
		save = rb_swallow(save);
		wasred = (save->red > 1);
	}
	((wasred == 0) ? rb_fix_rebalance(save, (save->children[0] != 0))
		: (save->red = 0));
}

/*
** These functions help rebalance the tree after node removals.
** It returns a positive integer when the tree no longer
** needs to be rebalanced.
*/

int				rb_rebal(t_node **p, t_node **s, int dir)
{
	int			flag;

	flag = 1;
	if ((*s)->red == 0 && CBOTHBLK((*s)))
	{
		(*s)->red = !(*s)->red;
		if ((*p)->red == 1)
			return (((*p)->red = 0) ? 1 : 1);
		return (0);
	}
	if (!IS_RED((*s)->children[!dir]))
		*s = rb_rotate(*s, !dir, 1);
	*p = rb_rotate(*p, dir, 0);
	*s = ((*p)->children[!dir]);
	if (CBOTHRED((*p)))
		rb_invert((*p));
	return ((*p)->red == 1 ? 1 : !((*s)->red = 0));
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
			rb_rotate(p, dir, 1);
			s = p->children[!dir];
		}
		if (s)
			if (rb_rebal(&p, &s, dir) == 1)
				return ;
		dir = (p->parent ? DIR(p) : dir);
		p = p->parent;
	}
}
