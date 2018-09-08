/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formati_module.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 19:13:11 by jkrause           #+#    #+#             */
/*   Updated: 2018/07/17 17:21:43 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Improved Format Module.
** The idea is not to allocate any extra memory.
*/

int					pad_write_module(char c, int repeats)
{
	while ((--repeats) >= 0)
		write_module(&c, 1);
	return (repeats);
}

int					prefixi(t_input *in, char *str, int write, int len)
{
	int					length;
	char				tmp[3];

	tmp[0] = 0;
	tmp[1] = 0;
	if ((in->flag_alt_mode && LC(in->type, 'x') && ft_strlen(str) == 0)
			|| (*str == '0' && !LC(in->type, 'd')
				&& in->error != -9) || LC(in->type, 'u'))
		return (0);
	if (in->length_extended == 4)
		ft_memcpy(&tmp, "-", 2);
	else if (in->module == 'i' && in->flag_all_signs_char != 0)
		tmp[0] = in->flag_all_signs_char;
	else if (in->module == 'i' && in->flag_alt_mode == 1 && CMP(in->type, 'x'))
		ft_memcpy(&tmp, "0x", 2);
	else if (in->module == 'i' && in->flag_alt_mode == 1 && CMP(in->type, 'X'))
		ft_memcpy(&tmp, "0X", 2);
	else if (in->module == 'i' && in->flag_alt_mode == 1
			&& CMP(in->type, 'o') && *str != '0')
		ft_memcpy(&tmp, "0", 2);
	tmp[2] = 0;
	length = ft_strlen(tmp);
	if (write != 0)
		write_module((char*)&tmp, (len < length && len >= 0 ? len : length));
	return (length);
}

void				precisei(t_input *in, char *str)
{
	int					precision;
	int					length;

	length = in->output_length;
	precision = (in->precision == INT_MIN ? INT_MIN : in->precision);
	if (precision != INT_MIN)
	{
		if (precision <= 0 && in->module != 'i')
		{
			length = precision + length;
			prefixi(in, str, 1, length);
		}
		else
			prefixi(in, str, 1, -1);
		if (precision > 0 && in->module == 'i')
			pad_write_module('0', precision);
	}
	else if (in->error != 3)
		prefixi(in, str, 1, -1);
	write_module(str, length);
}

void				widthi(t_input *in, char *str)
{
	int					width;
	int					length;

	length = in->output_length;
	if (length > 0 || CMP(in->type, 'c')
			|| (in->precision != INT_MIN && CMP(in->module, 'i')))
		length = prefixi(in, str, 0, -1)
			+ (CMP(in->type, 'c') && length < 1 ? 1 : 0)
			+ (((in->precision != INT_MIN && in->module != 'i') ||
				(in->module == 'i' && in->precision > 0)) ? in->precision : 0)
			+ length;
	width = in->width - length;
	if (width > 0 && !in->flag_left_justify
			&& in->precision == INT_MIN
			&& in->flag_zero_pad && in->module == 'i')
	{
		prefixi(in, str, 1, -1);
		in->error = 3;
		pad_write_module('0', width);
	}
	else if (width > 0)
		pad_write_module(' ', width);
}

int					formati_module(t_input *in, char *str)
{
	if (!in->output_length)
		in->output_length = ft_strlen(str);
	if (in->precision != INT_MIN)
		in->precision -= in->output_length;
	if (in->flag_left_justify)
	{
		precisei(in, str);
		widthi(in, str);
	}
	else if (CMP(in->type, 'c') && in->output_length == 0)
		widthi(in, str);
	else
	{
		widthi(in, str);
		precisei(in, str);
	}
	return (1);
}
