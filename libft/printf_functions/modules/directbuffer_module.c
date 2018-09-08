/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directbuffer_module.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:24:52 by jkrause           #+#    #+#             */
/*   Updated: 2018/07/18 15:04:33 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*g_direct_ptr;
size_t			g_direct_maxsize;
size_t			g_direct_cursize;

void			directbuffer_module_init(char *ptr, size_t max_length)
{
	if ((ssize_t)max_length == -1)
		return ;
	g_direct_ptr = ptr;
	g_direct_maxsize = max_length;
	g_direct_cursize = 0;
}

void			directbuffer_module_write(t_input *input, char *write)
{
	size_t		size;

	(void)input;
	if ((g_direct_maxsize - g_direct_cursize) == 0)
		return ;
	size = (int)input;
	if ((g_direct_maxsize - g_direct_cursize) < size)
		size = (g_direct_maxsize - g_direct_cursize) - 1;
	ft_memcpy(g_direct_ptr + g_direct_cursize, write, size);
	g_direct_cursize += size;
}

int				directbuffer_module_flush(t_input *input, void *nil)
{
	(void)input;
	(void)nil;
	return (g_direct_cursize);
}
