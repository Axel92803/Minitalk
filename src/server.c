/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iontanvu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:42:59 by iontanvu          #+#    #+#             */
/*   Updated: 2025/02/11 14:46:51 by iontanvu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	ft_btoa(int sig_n)
{
	static int	x;
	static int	bit;

	if (sig_n == SIGUSR1)
		(x |= (0x01 << bit));
	bit++;
	if (bit == 8)
	{
		if (x == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", x);
		x = 0;
		bit = 0;
	}
}

int	setup_signal_handlers(void)
{
	if (signal(SIGUSR1, ft_btoa) == SIG_ERR)
	{
		ft_printf("Error setting up SIGUSR1 handler\n");
		return (1);
	}
	if (signal(SIGUSR2, ft_btoa) == SIG_ERR)
	{
		ft_printf("Error setting up SIGUSR2 handler\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error, too many arguments\n");
		return (1);
	}
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	if (setup_signal_handlers() != 0)
		return (1);
	while (argc == 1)
	{
		pause();
	}
	return (0);
}
