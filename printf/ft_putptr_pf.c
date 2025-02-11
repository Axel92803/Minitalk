/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iontanvu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:06:13 by iontanvu          #+#    #+#             */
/*   Updated: 2024/03/30 15:11:17 by iontanvu         ###   ########.fr       */
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

static void	ft_put_ptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_pf(num + '0');
		else
			ft_putchar_pf(num - 10 + 'a');
	}
}

int	ft_putptr_pf(unsigned long long ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (count += write(1, "(nil)", 5));
	count = ft_putstr_pf("0x");
	ft_put_ptr(ptr);
	return (count + ft_len(ptr));
}
