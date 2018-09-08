/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltostr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 12:58:42 by jkrause           #+#    #+#             */
/*   Updated: 2018/07/16 17:42:42 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long					ft_pow(long a, long b)
{
	long					res;

	res = a;
	while (b-- > 0)
		res *= a;
	return (res);
}

static void					*interpret_mulcast(void *ptr, long base,
								long mul, int sign)
{
	long					ln;

	if (!sign)
		return ((void*)((unsigned long)ptr / ft_pow(base, mul) % base));
	else
	{
		ln = ((long)ptr / ft_pow(base, mul) % base);
		if (ln < 0)
			return ((void*)(ln *= -1));
	}
	return ((void*)ln);
}

static long					mulsize(void *value, int base, int sign)
{
	long					size;
	long					cpy;
	unsigned long			ucpy;

	cpy = (long)value;
	ucpy = (unsigned long)value;
	size = 0;
	if (!sign)
	{
		while (ucpy >= (unsigned long)base)
		{
			ucpy /= base;
			size++;
		}
	}
	else
	{
		while (cpy >= (long)base || cpy <= (long)-base)
		{
			cpy /= base;
			size++;
		}
	}
	return (size);
}

int							ft_ltostr_base(char *buffer, size_t bufsize,
								char *alpha, void *value)
{
	size_t					buffsize;
	unsigned long			ucpy;
	long					mul;
	int						sign;
	int						bass;

	if (!buffer || bufsize < 3)
		return (0);
	bufsize--;
	sign = (alpha[0] == '-' ? 1 : 0);
	(alpha[0] == ' ' || alpha[0] == '-' ? (void)alpha++ : (void)alpha);
	buffsize = 0;
	bass = ft_strlen(alpha);
	ucpy = (unsigned long)value;
	mul = mulsize(value, bass, sign);
	if (((long)value) < 0 && sign)
		buffer[buffsize++] = '-';
	while (mul-- > 0 && buffsize < bufsize)
		buffer[buffsize++] = alpha[(long)interpret_mulcast(value, bass,
				mul, sign)];
	if (buffsize < bufsize)
		buffer[buffsize++] = alpha[((sign && ((long)value) < 0
					? -((long)value) : ((unsigned long)value)) % bass)];
	buffer[buffsize++] = '\0';
	return (1);
}
