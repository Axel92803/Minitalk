/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un_pf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iontanvu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:05:53 by iontanvu          #+#    #+#             */
/*   Updated: 2024/03/30 14:28:42 by iontanvu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_un_pf(unsigned int u)
{
	static int	count;

	count = 0;
	if (u >= 10)
		ft_putnbr_un_pf(u / 10);
	count++;
	ft_putchar_pf(u % 10 + '0');
	return (count);
}
