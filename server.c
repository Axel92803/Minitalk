#include "minitalk.h"

void ft_btoa(sig_n)
{
    static  int i;
    static  int bit;

    bit = 0;
    if (sig_n == SIGUSR1)
        (i |= (0x01 << bit));
    bit++;
    if (bit == 8)
    {
        ft_printf("%c", i);
        i = 0;
        bit = 0;
    }
}

int main(int, char **)
{
    int pid;

	if (argc != 1)
	{
		ft_printf("Error, too few or too many arguments\n");
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