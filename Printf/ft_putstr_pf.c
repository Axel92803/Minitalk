#include "ft_printf.h"

int ft_putstr_pf(char *str)
{
    int count;

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