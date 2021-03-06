/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:41:07 by jkrause           #+#    #+#             */
/*   Updated: 2018/10/25 15:08:43 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Red black tree implementation for the purposes of understanding
** them and implementing them for Redzone.
** I can't imagine how long this will take...
*/

#ifndef RBTREE_H
# define RBTREE_H

# include "libft.h"

# define LEFT 0
# define RIGHT 1

typedef struct			s_node
{
	int				red;
	int				value;
	struct s_node	*parent;
	struct s_node	*children[2];
}						t_node;

t_node					*g_root;

t_node					*rb_initialize(t_node *parent, int value);
t_node					*rb_insert(t_node *root, int value);

t_node					*rb_search(t_node *root, int value);

/*
** TODO: Fix name
*/
t_node					*rb_swallow(t_node *n);

void					rb_invert(t_node *node);

void					rb_fix_insert_recurs(t_node *node);
void					rb_fix_insert(t_node *node);

void					rb_fix_rebalance(t_node *n, int dir);

void					rb_remove(t_node *q);

int						rb_assert(t_node *n);

t_node					*rb_rotate(t_node *n, int dir);

/*
** Temporary
*/

void					print_buds(t_node *root, int w);

/*
** "helper functions"
*/

# define IS_RED(n) (n != 0 && n->red == 1)

# define PARENT(n) n->parent
# define P(n) PARENT(n)
# define GP(n) n->parent->parent

# define ISCHILD(n, c) (n->parent->children[c] == n)
# define ISLCHILD(n) ISCHILD(n, 0)
# define ISRCHILD(n) ISCHILD(n, 1)

# define GETCHILD(n) (ISLCHILD(n) ? 0 : ISRCHILD(n) ? 1 : -1)
# define DIR(n) GETCHILD(n)

# define FGETCHILD(n) (n->parent != 0 && n->parent->value < n->value)

# define CHILD(n, c) n->children[c]
# define LCHILD(n) n->children[0]
# define RCHILD(n) n->children[1]

# define SIBLINGDIR(n, dir) n->parent->children[!dir]
# define UNCLEDIR(n, dir) n->parent->parent->children[!dir]
# define S0(n) (n->parent == 0 ? 0 : SIBLINGDIR(n, GETCHILD(n)))
# define SIBLING(n) S0(n)
# define D1(n) UNCLEDIR(n, GETCHILD(n->parent))
# define D0(n) (n->parent == 0 ? 0 : n->parent->parent == 0 ? 0 : D1(n))
# define UNCLE(n) D0(n)

# define SETBLKRED(b, r) b->red = 0; r->red = 1;

# define AB(n) ft_printf("**** rbtree abort: %s\n", n); exit(-1);
# define FAIL(n) ft_printf(""); AB(n)

/*
** Red Black tree "conditional functions"
*/

# define BOTHSAME(n1, n2) (n1->red == n2->red)

# define CCHILD(n, c, v) (CHILD(n, c) != 0 && CHILD(n, c)->red == v)

# define BOTHBLK(n1, n2) (BOTHSAME(n1,n2) && n1->red == 0)
# define BOTHRED(n1, n2) (BOTHSAME(n1,n2) && n1->red == 1)
# define CBOTHRED(n) (CCHILD(n, 0, 1) && CCHILD(n, 1, 1))
# define CB0(n) (CHILD(n, 0) == 0 && CHILD(n, 1) == 0)
# define CBOTHBLK(n) (CCHILD(n, 0, 0) && CCHILD(n, 1, 0) || CB0(n))

#endif
