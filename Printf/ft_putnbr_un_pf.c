#include "ft_printf.h"

int	ft_putnbr_un_pf(unsigned int u)
{
    static int count;

    count = 0;
	if (u >= 10)
		ft_putnbr_un_pf(u / 10);
        count++;
	ft_putchar_pf(u % 10 + '0');
    return (count);
}