#include "../inc/minitalk.h"

void ft_btoa(int sig_n)
{
    static  int x;
    static  int bit;

    bit = 0;
    if (sig_n == SIGUSR1)
        (x |= (0x01 << bit));
    bit++;
    if (bit == 8)
    {
        ft_printf("%c", x);
        x = 0;
        bit = 0;
    }
}

int main(int argc, char **argv)
{
    int pid;

	(void)argv;

	if (argc != 1)
	{
		ft_printf("Error, too many arguments\n");
		return (1);
	}
	pid = getpid();
	ft_printf("%d\n", pid);
	while (argc == 1)
	{
		signal(SIGUSR1, ft_btoa);
		signal(SIGUSR2, ft_btoa);
		pause ();
	}
	return (0);
}