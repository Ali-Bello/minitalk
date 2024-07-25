NAME = libftprintf.a

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_printf.c parsing.c d_functions.c p_functions.c\
	u_functions.c hex_functions.c s_functions.c c_functions.c\
	helpers.c helpers2.c print_functions.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)

.c.o:
	cc $(CFLAGS) -c $<
	ar rc $(NAME) $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

bonus: $(NAME)

re: fclean all

.SECONDARY: $(OBJS)
