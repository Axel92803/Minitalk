/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iontanvu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:14:35 by iontanvu          #+#    #+#             */
/*   Updated: 2024/03/30 14:15:30 by iontanvu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putchar_pf(int c);
int	ft_putstr_pf(char *str);
int	ft_putptr_pf(unsigned long long ptr);
int	ft_putnbr_pf(int n);
int	ft_putnbr_un_pf(unsigned int u);
int	ft_put_hex_pf(unsigned int num, const char flag);

#endif
