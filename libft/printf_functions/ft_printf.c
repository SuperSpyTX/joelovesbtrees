/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 11:15:43 by jkrause           #+#    #+#             */
/*   Updated: 2018/08/14 13:01:39 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					search(t_input *parsed, char *fmt)
{
	char				*search;

	search = (char*)fmt;
	ft_bzero(parsed, sizeof(t_input));
	while (*search != '\0')
	{
		search = ft_strchr(fmt, '%');
		if (search == 0)
			break ;
		module_call(PARSEMODULE_PARSE, parsed, search);
		parsed->original = search;
		return (1);
	}
	return (0);
}

int					ft_printf(const char *fmt, ...)
{
	va_list				start;
	t_input				iflag;
	char				*current;

	current = (char*)fmt;
	module_init();
	g_modules[WRITEMODULE_WRITE] = (t_module)bufferwrite_module_write;
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

char				*ft_sprintf(const char *fmt, ...)
{
	va_list				start;
	t_input				iflag;
	char				*current;

	current = (char*)fmt;
	module_init();
	g_modules[WRITEMODULE_WRITE] = (t_module)bufferstring_module_write;
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
	write_module("", 1);
	return (bufferstring_module_retrieve());
}
