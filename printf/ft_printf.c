#include "ft_printf.h"

int parse_format(char flag, va_list ap)
{
    int count;

    count = 0;
    if (flag == 'c')
        count = ft_putchar_pf(va_arg(ap, int));
    else if (flag == 's')
        count = ft_putstr_pf(va_arg(ap, char *));
    else if (flag == 'p')
        count = ft_putptr_pf(va_arg(ap, unsigned long long));
    else if (flag == 'd' || flag == 'i')
        count = ft_putnbr_pf(va_arg(ap, int));
    else if (flag == 'u')
        count = ft_putnbr_un_pf(va_arg(ap, unsigned int));
    else if (flag == 'x' || flag == 'X')
        count = ft_put_hex_pf(va_arg(ap, unsigned int), flag);
    else if (flag == '%')
        count += write(1, "%", 1);
    else
        count += write(1, &flag, 1);
    return (count); 
}

int ft_printf(const char *format, ...)
{
   va_list ap;
   int count;

   va_start(ap, format);
   count = 0;
   while (*format != '\0')
   {
        if (*format == '%')
            count += parse_format(*(++format), ap);
        else
            count += write(1, format, 1);
        format++;
   }
   va_end(ap);
   return (count);
}