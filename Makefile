CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME1 = client

NAME2 = server

SRC1 = client.c

SRC2 = server.c

LIBRARY = libftprintf.a

LIBRARYDIR = ft_printf

LIBRARYSRCS = ft_printf/c_functions.c ft_printf/d_functions.c  ft_printf/p_functions.c ft_printf/ft_printf.c\
			ft_printf/s_functions.c ft_printf/u_functions.c ft_printf/hex_functions.c \
			ft_printf/helpers.c ft_printf/helpers2.c ft_printf/parsing.c ft_printf/print_functions.c

all : $(LIBRARY) $(NAME1) $(NAME2)

$(LIBRARY) : $(LIBRARYDIR) $(LIBRARYSRCS)
	make -C $(LIBRARYDIR)

$(NAME1) : $(SRC1)
	$(CC) $(CFLAGS) $(SRC1) $(LIBRARYDIR)/$(LIBRARY) -o $(NAME1)

$(NAME2) : $(SRC2)
	$(CC) $(CFLAGS) $(SRC2) $(LIBRARYDIR)/$(LIBRARY) -o $(NAME2)

clean :
	make -C $(LIBRARYDIR) clean

fclean : clean
	rm -f $(LIBRARYDIR)/$(LIBRARY)
	rm -f $(NAME1)
	rm -f $(NAME2)

re : fclean all
