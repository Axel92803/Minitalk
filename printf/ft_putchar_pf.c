#include "ft_printf.h"

int    ft_putchar_pf(int c)
{
    return (write(1, &c, 1));
}