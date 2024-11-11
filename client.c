#include "minitalk.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	int			sign_count;
	long int	res;

	sign = 1;
	sign_count = 0;
	res = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		sign_count++;
		if (*nptr == '-' && sign_count == 1)
			sign = -1;
		else if (*nptr == '+' && sign_count == 1)
			sign = 1;
		else
			sign = 0;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
		res = (res * 10) + (*nptr++ - '0');
	return (res * sign);
}

void ft_atob(int pid, char c)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if ((c & (0x01 << bit)))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(500);
        bit++;
    }

}

int main(int argc, char **argv)
{
    int pid;
    int x;

    if (argc == 3)
    {
        pid = ft_atoi(argv[1]);
        while (argv[2][x] != "\0")
        {
            ft_atob(argv[2][x]);
            x++;
        }
        else
        {
            ft_printf("Error\n");
            return (1);
        }
    }
    else
    {
        ft_printf("Error, too many or too few arguments");
        return (1);
    }
    return (0);
}