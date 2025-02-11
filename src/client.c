/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iontanvu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:36:57 by iontanvu          #+#    #+#             */
/*   Updated: 2025/02/11 14:42:45 by iontanvu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_atob(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)))
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("Error sending SIGUSR1\n");
				return (1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("Error sending SIGUSR2\n");
				return (1);
			}
		}
		usleep(1000);
		bit++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	x;

	x = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
		{
			ft_printf("Error: Invalid PID\n");
			return (1);
		}
		while (argv[2][x] != '\0')
		{
			if (ft_atob(pid, argv[2][x]) != 0)
				return (1);
			x++;
		}
		if (ft_atob(pid, '\0') != 0)
			return (1);
	}
	else
	{
		ft_printf("Error, too many or too few arguments");
		return (1);
	}
	return (0);
}
