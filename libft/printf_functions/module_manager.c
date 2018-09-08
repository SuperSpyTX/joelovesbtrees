/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 17:16:16 by jkrause           #+#    #+#             */
/*   Updated: 2018/07/17 10:38:44 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					module_init(void)
{
	g_modules[WRITEMODULE_WRITE] = (t_module)bufferwrite_module_write;
	g_modules[WRITEMODULE_FLUSH] = (t_module)bufferwrite_module_flush;
	g_modules[PARSEMODULE_PARSE] = (t_module)parse_module;
	g_modules[FORMATMODULE_FORMAT] = (t_module)formati_module;
	g_modules[ASTERISKMODULE_PARSE] = (t_module)asterisks_module;
	module_init2();
}

void					module_init2(void)
{
	MULTIREG('d', (t_module)integer_module);
	MULTIREG('i', (t_module)integer_module);
	MULTIREG('x', (t_module)integer_module);
	MULTIREG('u', (t_module)integer_module);
	MULTIREG('o', (t_module)integer_module);
	MULTIREG('p', (t_module)integer_module);
	MULTIREG('s', (t_module)string_module);
	MULTIREG('c', (t_module)string_module);
	g_modules['n'] = (t_module)memorywrite_module;
	g_modules['%'] = (t_module)string_module;
}

int						module_call(char key, t_input *input, void *args)
{
	if (!g_modules[(int)key])
		return (-1);
	return (g_modules[(int)key](input, args));
}

int						write_flush(int code)
{
	return (module_call(WRITEMODULE_FLUSH, 0, (void*)(intptr_t)code));
}

int						write_module(char *str, int length)
{
	int					len;

	len = (length < 0 ? ft_strlen(str) : length);
	module_call(WRITEMODULE_WRITE, (t_input*)(intmax_t)len, str);
	return (len);
}
