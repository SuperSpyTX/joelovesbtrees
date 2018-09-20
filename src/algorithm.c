/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 23:29:20 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/08 13:31:04 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

/*
** Used for comparison only.
*/

void			rb_fix_insert_recurs(t_node *q)
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
		return (rb_fix_insert_recurs(rb_rotate(g, !GETCHILD(p), 1)));
	}
	return (rb_fix_insert_recurs(q->parent));
}
