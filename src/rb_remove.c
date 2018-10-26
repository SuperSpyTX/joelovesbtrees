/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:31:50 by jkrause           #+#    #+#             */
/*   Updated: 2018/10/25 19:43:32 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_node			*rb_find_edge(t_node *q)
{
	t_node		*edgelord;

	ft_printf("Finding edge for %d\n", q->value);
	edgelord = q->children[0];
	while (edgelord->children[1] != 0)
		edgelord = edgelord->children[1];
	return (edgelord);
}

void			rb_remove(t_node *q)
{
	t_node		*save;
	int			red;

	ft_printf("Removing node %d (isred: %d)\n", (q ? q->value : -1), IS_RED(q));
	if (q->children[0] == 0 || q->children[1] == 0)
	{
		ft_printf("Either children is null, lets use it.\n");
		red = IS_RED(q) || IS_RED(CHILD(q, CHILD(q, 0) == 0));
		save = rb_swallow(q);
		if (save->red == 2)
		{
			ft_printf("Save->red saved to two.\n");
			save->red = 0;
			red = 1;
		}
		if (!save && !g_root)
			return ;
	}
	else
	{
		ft_printf("Need to use our edgelords.\n");
		save = rb_find_edge(q);
		q->value = save->value;
		red = IS_RED(save);
		save = rb_swallow(save);
	}
	ft_printf("red: %d\n", red);
	(!red ? rb_fix_rebalance(save, (save->children[0] != 0)) : (save->red = 0));
	ft_printf("Rebalancing finished.\n");
}

/*
** These functions help rebalance the tree after node removals.
** It returns a positive integer when the tree no longer
** needs to be rebalanced.
*/

int				rb_rebal(t_node **p, t_node **s, int dir)
{
	int				wasred;

	ft_printf("In rebal func: p: %d, s: %d\n", ((*p) ? (*p)->value : -1),
			((*s) ? (*s)->value : -1));
	if (p && (*s)->parent && (*s)->parent != (*p))
	{
		ft_printf("Dangling pointer? P: %d S->P: %d\n", (*p)->value, (*s)->parent->value);
		AB("Dangling parent pointer?");
	}
	ft_printf("BOTHBLK: %d\n", CBOTHBLK((*s)));
	if ((*s)->red == 0 && CBOTHBLK((*s)))
	{
		ft_printf("Sibling black and both children black/null\n");
		(*s)->red = 1;
		if ((*p)->red == 1)
		{
			ft_printf("Found red node.\n");
			return (((*p)->red = 0) ? 1 : 1);
		}
		ft_printf("P: %d is still black...\n", (*p)->value);
		print_buds(g_root, -1);
		return ((*p)->parent == 0 ? 1 : 0);
	}
	ft_printf("Doing regular rotations...\n");
	if (!IS_RED((*s)->children[!dir]))
	{
		ft_printf("Sibling child[!dir] not red.\n");
		(*s)->red = 1;
		*s = rb_rotate(*s, !dir);
		(*s)->red = 0;
	}
	wasred = IS_RED((*p));
	*p = rb_rotate(*p, dir);
	*s = ((*p)->children[!dir]);
	ft_printf("old parent is %d\n", ((*p)->children[dir]->value));
	ft_printf("new parent is %d\n", ((*p)->value));
	ft_printf("new sibling is %d\n", ((*p)->children[!dir]->value));
	(*s)->red = 0;
	ft_printf("previous parent red? %d\n", wasred);
	if (wasred)
	{
		(*p)->red = 1;
		(*p)->children[dir]->red = 0;
	}
	print_buds(g_root, -1);
	return (1);
}

/*
** Broken test cases (9-17-18):
**
** export DELETE_SIZE=2; ./rbtree (seq 0 21)
*/

void			rb_fix_rebalance(t_node *n, int dir)
{
	//int			dir;
	t_node		*p;
	t_node		*s;
	t_node		*pp;

	if (!n || (n == g_root && CB0(n)))
		return ;
	p = n;
	while (p)
	{
		ft_printf("Rebalancing on p node: %d\n", (p != 0 ? p->value : -1));
		s = p->children[!dir];
		if (s == 0)
		{
			ft_printf("DIR: %d\n", dir);
			if (s == 0)
				ft_printf("Sibling is null.  What the fuck is happening?\n");
			else if (s == pp)
				ft_printf("Sibling is the previous parent.\n");
			AB("Sibling isn't the right one.");
		}
		/*s = p->children[dir];
		if (s == q)
		{
			AB("WTF");
		}*/
		if (IS_RED(s))
		{
			ft_printf("Sibling is red (%d), rotate.\n", s->value);
			s = rb_rotate(p, dir);
			ft_printf("New sibling: %d\nNew parent: %d\n", s->value, (s->parent ? s->parent->value : -1));
			SETBLKRED(s, p);
			continue;
		}
		ft_printf("Rebalance needed on node: %d\n", s->value);
		if (rb_rebal(&p, &s, dir) == 1)
		{
			ft_printf("Stop here.\n");
			return ;
		}
		dir = DIR(p);
		p = p->parent;
		ft_printf("Changing direction.\n");
		if (p == pp)
		{
			ft_printf("Rebalancing on p node: %d\n", (p->parent->value));
			AB("Lance Armstrong Cyclic Loop Detected.");
		}
		pp = p;
	}
}
