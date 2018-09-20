/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:31:50 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/20 14:56:12 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

t_node			*rb_find_edge(t_node *q, int *wasred)
{
	t_node		*edgelord;

	ft_printf("Finding edge for %d\n", q->value);
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

	ft_printf("Removing node %d (isred: %d)\n", (q ? q->value : -1), IS_RED(q));
	if (q->children[0] == (void*)(intmax_t)(wasred = 0) || q->children[1] == 0)
	{
		ft_printf("Either children is null, lets use it.\n");
		if (CHILD(q, CHILD(q, 0) == 0) != 0)
			wasred = IS_RED(CHILD(q, CHILD(q, 0) == 0));
		save = rb_swallow(q);
		if (!save && !g_root)
			return;
		ft_printf("IS_RED(save %d): %d\n", (save ? save->value : -1), save->red > 1);
		wasred = (save->red > 1);
	}
	else
	{
		ft_printf("Need to use our edgelords.\n");
		save = rb_find_edge(q, &wasred);
		q->value = save->value;
		save = rb_swallow(save);
		wasred = (save->red > 1);
	}
	ft_printf("wasred: %d\n", wasred);
	((wasred == 0) ? rb_fix_rebalance(save, (save->children[0] != 0)) : (save->red = 0));
	ft_printf("Rebalancing finished.\n");
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
		(*s)->red = !(*s)->red;
		if ((*p)->red == 1/* || (*p) == g_root*/)
		{
			if ((*p)->red == 1)
				ft_printf("Found red node.\n");
			if ((*p) == g_root)
				ft_printf("Found root node.\n");
			return (((*p)->red = 0) ? 1 : 1);
		}
		ft_printf("P: %d is still black...\n", (*p)->value);
		print_buds(g_root, -1);
		return (0);
	}
	ft_printf("Doing regular rotations...\n");
	if (!IS_RED((*s)->children[!dir])/* && ((*s)->children[dir] && (*s)->children[dir]->children[!dir]) */)
	{
		ft_printf("Sibling child[dir] not red.\n");
		*s = rb_rotate(*s, !dir, 1);
	}
	*p = rb_rotate(*p, dir, 0);
	*s = ((*p)->children[!dir]);
	ft_printf("children[dir] is %d\n", ((*p)->children[dir]->value));
	ft_printf("children[!dir] is %d\n", ((*p)->children[!dir]->value));
	//(*p)->red = 0;
	//(*p)->children[dir]->red = 1;
	/*if ((*p)->children[!dir]->red == 1)
	{
		ft_printf("Setting nephew to 0.\n");
		(*p)->children[!dir]->red = 0;
		return (1);
		//rb_invert((*p));
		//(*p)->children[dir]->red = 1;
	}*/
	if (CBOTHRED((*p)))
		rb_invert((*p));
	print_buds(g_root, -1);
	return ((*p)->red == 1 ? 1 : !((*s)->red = 0));
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
		//p = (q->parent ? q->parent : q);
		s = p->children[!dir];
		if (s == pp || s == 0)
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
			rb_rotate(p, dir, 1);
			s = p->children[!dir];
		}
		if (s)
		{
			ft_printf("Rebalance needed on node: %d\n", s->value);
			if (rb_rebal(&p, &s, dir) == 1)
			{
				ft_printf("Stop here.\n");
				return ;
			}
		}
		if (p->parent && p->parent == pp)
		{
			ft_printf("Rebalancing on p node: %d\n", (p->parent->value));
			AB("Lance Armstrong Cyclic Loop Detected.");
		}
		pp = p;
		dir = (p->parent ? DIR(p) : dir);
		p = p->parent;
		ft_printf("New dir: %d\n", dir);
		//q = p->parent;
	}
}
