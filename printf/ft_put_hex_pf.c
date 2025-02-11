/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iontanvu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:04:35 by iontanvu          #+#    #+#             */
/*   Updated: 2024/03/30 14:21:40 by iontanvu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned long long num)
{
	int	count;

	count = 0;
	while (num != 0)
	{
		num /= 16;
		count++;
	}
	return (count);
}

static int	ft_hex(unsigned int num, const char flag)
{
	if (num >= 16)
	{
		ft_hex(num / 16, flag);
		ft_hex(num % 16, flag);
	}
	else
	{
		if (num <= 9)
			ft_putchar_pf(num + '0');
		else
		{
			if (flag == 'x')
				ft_putchar_pf(num - 10 + 'a');
			if (flag == 'X')
				ft_putchar_pf(num - 10 + 'A');
		}
	}
	return (1);
}

int	ft_put_hex_pf(unsigned int num, const char flag)
{
	int	count;

	count = 0;
	if (num == 0)
	{
		return (ft_putchar_pf('0'));
		count++;
	}
	else
		ft_hex(num, flag);
	return (count + ft_len(num));
}
