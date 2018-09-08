/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_module.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 13:23:30 by jkrause           #+#    #+#             */
/*   Updated: 2018/07/18 15:39:12 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Dropped wide-string/char conversion support in favor of
** more performant printf.
*/

void				write_conv(t_input *input, void *conv)
{
	int					ch;
	char				*str;

	ch = 0;
	str = 0;
	if (CMP(input->type, 'c'))
		ch = (int)conv;
	else
		str = (char*)conv;
	input->module = 's';
	if (CMP(input->type, 'c'))
		module_call(FORMATMODULE_FORMAT, input, (char*)&ch);
	else if (str)
		module_call(FORMATMODULE_FORMAT, input, str);
	else
		write_module("(null)", 6);
}

int					string_aliasing(t_input *input)
{
	if (CMP(input->type, '%'))
	{
		input->type = 's';
		input->precision = INT_MIN;
		write_conv(input, "%");
		return (1);
	}
	return (0);
}

/*
** Swallow the argument if the call is unsupported.
** While this should be handled in the appropriate location,
** it is hopefully to fix a crash bug.
*/

int					string_module(t_input *input, va_list *ptr)
{
	if (string_aliasing(input))
		return (1);
	else if (CMP(input->type, 'c') || CMP(input->type, 's'))
		write_conv(input, va_arg(*ptr, void*));
	else
		va_arg(*ptr, void*);
	return (1);
}
