/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 20:22:31 by jkrause           #+#    #+#             */
/*   Updated: 2018/07/09 15:16:02 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** At this point, my printf body functions are gonna be duplicated.
** But the new optimizations for avoiding malloc() use is awesome.
*/

int				ft_snprintf(char *ptr, size_t max, const char *fmt, ...)
{
	va_list				start;
	t_input				iflag;
	char				*current;

	current = (char*)fmt;
	module_init();
	g_modules[WRITEMODULE_WRITE] = (t_module)directbuffer_module_write;
	g_modules[WRITEMODULE_FLUSH] = (t_module)directbuffer_module_flush;
	directbuffer_module_init(ptr, max);
	va_start(start, fmt);
	while (search(&iflag, current) != 0)
	{
		write_module(current, (iflag.original - current));
		module_call(ASTERISKMODULE_PARSE, &iflag, &start);
		if (iflag.error || module_call(iflag.type, &iflag, &start) == 0)
		{
			write_flush(-1);
			return (0);
		}
		current += (iflag.original - current) + iflag.input_length + 1;
	}
	write_module(current, ft_strlen(current));
	va_end(start);
	return (write_flush(0));
}
