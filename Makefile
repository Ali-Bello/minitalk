CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME1 = client
NAME2 = server
BNAME1 = client_bonus
BNAME2 = server_bonus
SRC1 = client.c ft_atoi.c
SRC2 = server.c
BSRC1 = client_bonus.c ft_atoi.c
BSRC2 = server_bonus.c
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

$(BNAME1) : $(BSRC1)
	$(CC) $(CFLAGS) $(BSRC1) $(LIBRARYDIR)/$(LIBRARY) -o $(BNAME1)

$(BNAME2) : $(BSRC2)
	$(CC) $(CFLAGS) $(BSRC2) $(LIBRARYDIR)/$(LIBRARY) -o $(BNAME2)

clean :
	make -C $(LIBRARYDIR) clean

fclean : clean
	rm -f $(LIBRARYDIR)/$(LIBRARY)
	rm -f $(NAME1) $(NAME2) $(BNAME1) $(BNAME2)


re : fclean all

bonus : $(LIBRARY) $(BNAME1) $(BNAME2)
