#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int ft_printf(const char *format, ...);
int ft_putchar_pf(int c);
int ft_putstr_pf(char *str);
int ft_putptr_pf(unsigned long long ptr);
int ft_putnbr_pf(int n);
int	ft_putnbr_un_pf(unsigned int u);
int ft_put_hex_pf(unsigned int num, const char format);

#endif