/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 13:12:36 by jkrause           #+#    #+#             */
/*   Updated: 2018/09/13 15:04:37 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbtree.h"
#define FAIL2(n,a,b) FAIL(ft_sprintf("%s (%d != %d)",n,a,b))

/*
** C can be pretty lame sometimes, since macros can't be
** nested in an if condition if there's no brackets,
** otherwise clang messes it up and will immediately fail
** regardless of actual result.
*/

void			fail(char *str)
{
	FAIL(str);
}

void			fail2(char *str, int a, int b)
{
	print_buds(g_root, -1);
	FAIL2(str, a, b);
}

/*
** This is a tester function for the rbtree.
** This will call abort() if the tree is invalid.
**
** Note: I might let this fail norm, even tho it doesn't matter lmao.
** Note: >= values cannot be properly asserted, as they will eventually just get
** rotated anyways.  Also they will help with node deletion.
**
** Norminette errors are normal, as this is only meant for debugging now.
*/

int				rb_assert(t_node *n)
{
	int			lh;
	int			rh;

	//ft_printf("AssertNode: %d is Red? %d\n", (n == 0 ? -1 : n->value), (n == 0 ? -1 : n->red));
	if (!n)
		return (1);
	if (n->children[0] == 0 && n->children[1] == 0)
	{
		//ft_printf("No children(%d): return appropriate value\n", n->value);
		return (n->red == 1 ? 0 : 1);
	}
	if ((n->children[0] && n->children[0]->parent != n)
			|| (n->children[1] && n->children[1]->parent != n))
	{
		ft_printf("**** rb assert: Found dangling parent on node %d (p: %d).\n", n->value, (n->parent ? n->parent->value : -1));
		print_buds(g_root, -1);
		abort();
	}
	if (n->red == 0 && (n->children[0] != 0 && n->children[0]->red == 0) &&
			(n->children[1] != 0 && n->children[1] == 0))
	{
		ft_printf("**** rb assert: Got a B violation (p -> l and r children) (at %d p: %d)\n", n->value, (n->parent ? n->parent->value : -1));
		print_buds(g_root, -1);
		abort();
	}
	if (IS_RED(n) == 1 && (IS_RED(n->children[0]) || IS_RED(n->children[1])))
	{
		ft_printf("**** rb assert: Red violation (RedParent->RedChild) (node: %d, p: %d)\n", n->value, (n->parent ? n->parent->value : -1));
		print_buds(g_root, -1);
		abort();
	}
	if (n->children[LEFT] != 0 && n->children[0]->value > n->value)
	{
		ft_printf("**** rb assert: B-tree violation (LChild->Val > Node->Value) (%d > %d)", n->children[0]->value, n->value);
		print_buds(g_root, -1);
		abort();
	}
	if (n->children[RIGHT] != 0 && n->children[1]->value < n->value)
	{
		ft_printf("B-tree violation (RChild->Val < Node->Value) (%d < %d)", n->children[1]->value, n->value);
		print_buds(g_root, -1);
		abort();
	}
	lh = rb_assert(n->children[LEFT]);
	rh = rb_assert(n->children[RIGHT]);
	//ft_printf("%d %d\n", lh, rh);
	if (lh != 0 && rh != 0 && lh != rh)
	{
		fail2("Black-height violation (LH != RH)", lh, rh);
	}
	//ft_printf("Return value(%d): %d\n", n->value, (n->red == 1 ? lh : lh + 1));
	if (lh == 0 || rh == 0)
		return (0);
	return (n->red == 1 ? lh : lh + 1);
}
