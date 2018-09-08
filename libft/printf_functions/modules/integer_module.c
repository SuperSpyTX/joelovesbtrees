/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_module.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:23:49 by jkrause           #+#    #+#             */
/*   Updated: 2018/07/17 18:33:47 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				*magic_convert(t_input *input, va_list ptr, int sign)
{
	t_magicnum			number;
	unsigned long long	num;

	num = va_arg(ptr, unsigned long long);
	number = (t_magicnum)num;
	if (CMP(input->length, 'l' && !sign))
		return (void*)(input->length_extended ? num : number.ulong);
	else if (CMP(input->length, 'l') || CMP(input->length, 't'))
		return (void*)(input->length_extended ? number.llong : number.slong);
	else if (CMP(input->length, 'h') && !sign)
		return ((void*)(input->length_extended
				? (intptr_t)number.uchar : (intptr_t)number.ushort));
	else if (CMP(input->length, 'h'))
		return ((void*)(input->length_extended
				? (intptr_t)number.schar : (intptr_t)number.sshort));
	else if (CMP(input->length, 'j'))
		return ((void*)number.intmax);
	else if (CMP(input->length, 'z') && !sign)
		return ((void*)number.usize_t);
	else if (CMP(input->length, 'z'))
		return ((void*)number.sssize_t);
	else if (!sign)
		return ((void*)(intptr_t)number.uint);
	return ((void*)(intptr_t)number.sint);
}

int					integer_conv(t_input *input, va_list ptr, char *alpha)
{
	char			buffer[40];
	char			alphabuf[32];
	int				allength;
	int				sign;

	sign = 1;
	allength = ft_strlen(alpha);
	alpha = ft_memcpy(alphabuf, alpha, (allength > 32 ? 32 : allength));
	alpha[allength] = 0;
	sign = ((!LC(input->type, 'd') && !LC(input->type, 'i')) ? 0 : sign);
	sign = ((CMP(input->type, 'u') || ft_strlen(alpha + 1) != 10) ? 0 : sign);
	(sign == 1 ? alpha[0] = '-' : (void)alpha);
	ft_ltostr_base(buffer, 40, alpha,
			magic_convert(input, ptr, sign));
	input->module = 'i';
	if (buffer[0] == '-')
	{
		input->length_extended = 4;
		module_call(FORMATMODULE_FORMAT, input, buffer + 1);
	}
	else if (buffer[0] == '0' && input->precision != INT_MIN)
		module_call(FORMATMODULE_FORMAT, input, "");
	else
		module_call(FORMATMODULE_FORMAT, input, buffer);
	return (1);
}

void				aliasing(t_input *input)
{
	if (CMP(input->type, 'D'))
	{
		input->length = 'l';
		input->type = 'd';
		input->length_extended = 0;
	}
	else if (CMP(input->type, 'p'))
	{
		input->length = 'l';
		input->type = 'x';
		input->error = -9;
		input->flag_alt_mode = 1;
		input->length_extended = 0;
	}
	else if (CMP(input->type, 'U'))
	{
		input->length = 'l';
		input->type = 'u';
	}
}

int					integer_module(t_input *input, va_list *ptr)
{
	aliasing(input);
	if (LC(input->type, 'd') || LC(input->type, 'u')
			|| LC(input->type, 'i'))
		return (integer_conv(input, *ptr, " 0123456789"));
	else if (CMP(input->type, 'x'))
		return (integer_conv(input, *ptr, " 0123456789abcdef"));
	else if (CMP(input->type, 'X'))
		return (integer_conv(input, *ptr, " 0123456789ABCDEF"));
	else if (LC(input->type, 'o'))
		return (integer_conv(input, *ptr, " 01234567"));
	return (1);
}
