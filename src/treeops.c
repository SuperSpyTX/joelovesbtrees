/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:12:10 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/20 15:53:48 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"

/*
** TODO: Change this code to use pointer references
** from an array.
*/

/*
** We want to not actually call malloc() here, but for
** demonstration purposes we will simply do it here.
**
** This would normally come from the array.
*/

t_node			*rb_initialize(t_node *parent, int value)
{
	t_node		*node;

	node = (t_node*)malloc(sizeof(t_node));
	node->red = 1;
	node->value = value;
	node->parent = parent;
	node->children[0] = 0;
	node->children[1] = 0;
	return (node);
}

void			rb_invert(t_node *n)
{
	t_node		*p;

	p = n->parent;
	n->red = !n->red;
	(n->children[0] ? n->children[0]->red = !n->red : (void)n);
	(n->children[1] ? n->children[1]->red = !n->red : (void)n);
	g_root->red = 0;
}

/*
** Searches the rbtree for a particular node, where duplicates are allowed.
** Only the latest duplicate will resolve for now.
** I should write a function that would allow skipping of N duplicates
** before returning the node.
*/

t_node			*rb_search(t_node *root, int value)
{
	t_node		*cur;

	cur = root;
	while (cur)
	{
		if (cur->value == value)
			break ;
		cur = cur->children[(cur->value <= value)];
	}
	return (cur);
}

/*
** Another yet working solution.
*/

t_node			*rb_rotate(t_node *q, int dir, int setcolors)
{
	t_node		*p;
	t_node		*odir;

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
		q->red = 1;
		q->parent->red = 0;
	}
	if (p == 0)
	{
		g_root = odir;
		g_root->red = 0;
	}
	return (odir);
}

/*
** This actually removes the node.
*/

t_node			*rb_swallow(t_node *n)
{
	t_node		*child;

	if (n->children[0] == 0 && n->children[1] == 0)
	{
		(g_root == n ? g_root = 0 : (void)0);
		if (n->parent)
			n->parent->children[GETCHILD(n)] = 0;
		(n->red == 1 ? n->parent->red = 2 : (void)0);
		((child = n->parent) ? free(n) : free(n));
		return (child);
	}
	child = n->children[CHILD(n, 0) == 0];
	if (n->parent)
	{
		(child->red == 1 ? child->red = 2 : (void)0);
		n->parent->children[GETCHILD(n)] = child;
	}
	child->parent = n->parent;
	if (!child->parent)
	{
		g_root = child;
		g_root->red = 0;
	}
	free(n);
	return (child);
}
