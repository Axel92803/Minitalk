#include "ft_printf.h"

static int    ft_len(unsigned long long num)
{
    int    count;

    count = 0;
    while (num != 0)
    {
        num /= 16;
        count++;
    }
    return (count);
}

static void    ft_put_ptr(unsigned long long num)
{
    if (num >= 16)
    {
        ft_put_ptr(num / 16);
        ft_put_ptr(num % 16);
    }
    else
    {
        if (num <= 9)
            ft_putchar_pf(num + '0');
        else
            ft_putchar_pf(num - 10 + 'a');
    }
}

int    ft_putptr_pf(unsigned long long ptr)
{
    int count;
    int temp;

    count = 0;
    temp = ft_putstr_pf("0x");
    if (temp < 0)
		return (-1);
    else
		count += temp;
    if (ptr == 0)
    {
        if (ft_putchar_pf('0') < 0)
			return (-1);
        count++;
    }
    else
        ft_put_ptr(ptr);
    return (count + ft_len(ptr));
}