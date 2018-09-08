/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferstring_module.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 16:42:25 by jkrause           #+#    #+#             */
/*   Updated: 2018/08/14 12:41:33 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*g_bufferstr;
int					g_bufferstrsize;

int					bufferstring_module_write(t_input *input, char *write)
{
	int					size;

	size = (int)input;
	g_bufferstr = expand_write(write, size, g_bufferstr, &g_bufferstrsize);
	return (1);
}

int					bufferstring_module_flush(t_input *input, void *nil)
{
	(void)input;
	(void)nil;
	return (g_bufferstrsize);
}

char				*bufferstring_module_retrieve(void)
{
	char			*buffer;

	buffer = g_bufferstr;
	g_bufferstr = 0;
	g_bufferstrsize = 0;
	return (buffer);
}
