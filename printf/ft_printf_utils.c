#include "ft_printf.h"

int    ft_putchar_pf(int c)
{
    return (write(1, &c, 1));
}

int ft_putstr_pf(char *str)
{
    int counter;

    counter = 0;

    if (!str)
        str = "(null)";
    while (*str != '\0')
    {
        ft_putchar_pf((int)*str);
        counter++;
        str++;
    }
    return (counter);
}

int    ft_ptr_len(intptr_t num)
{
    int    len;

    len = 0;
    while (num != 0)
    {
        len++;
        num = num / 16;
    }
    return (len);
}

void    ft_put_ptr(intptr_t num)
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
    int    print_length;

    print_length = 0;
    print_length += write(1, "0x", 2);
    if (ptr == 0)
        print_length += write(1, "0", 1);
    else
    {
        ft_put_ptr(ptr);
        print_length += ft_ptr_len(ptr);
    }
    return (print_length);
}

int ft_putnbr_pf(int n)
{
    int count;

    count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		count += 11;
		return count;
	}
	if (n < 0)
	{
		ft_putchar_pf('-');
		ft_putnbr_pf(n * -1);
        count += 1;
	}
	else
	{
		if (n > 9)
			ft_putnbr_pf(n / 10);
            count++;
		ft_putchar_pf(n % 10 + '0');
	}
    return (count);
}

int	ft_putnbr_un_pf(unsigned int u)
{
    int count;

    count = 0;
	if (u >= 10)
		ft_putnbr_un_pf(u / 10);
        count++;
	ft_putchar_pf(u % 10 + '0');
    return (count);
}