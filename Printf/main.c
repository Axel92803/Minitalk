#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
    int a = 0;
    int *aa = &a;
    /*long m = -2147483648;
    long mx = 2147483647;
    long *min = &m;
    long *max = &mx;*/


    ft_printf(" %p ", aa);
    write(1, "\n", 1);
    printf(" %p %p ", aa, aa);
}
