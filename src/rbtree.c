/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:48:29 by jkrause           #+#    #+#             */
/*   Updated: 2018/08/09 13:40:10 by jkrause          ###   ########.fr       */
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
