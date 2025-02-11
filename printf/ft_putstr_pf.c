/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iontanvu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:06:34 by iontanvu          #+#    #+#             */
/*   Updated: 2024/03/30 14:41:50 by iontanvu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_pf(char *str)
{
	int	count;

	count = 0;
	if (!str)
		str = "(null)";
	while (*str != '\0')
	{
		ft_putchar_pf(*str);
		count++;
		str++;
	}
	return (count);
}
