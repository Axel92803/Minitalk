NAME	= libftprintf.a

SRCS	= ft_printf.c \
		ft_putchar_pf.c \
		ft_putstr_pf.c \
		ft_putptr_pf.c \
		ft_putnbr_pf.c \
		ft_putnbr_un_pf.c \
		ft_put_hex_pf.c \

OFILES	= $(SRCS:.c=.o)

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OFILES)
			ar rcs $(NAME) $(OFILES)

clean:
			$(RM) $(OFILES)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re