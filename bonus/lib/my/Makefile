##
## Makefile for repo_igniter in /home\benoit.lormeau\.repo_ignit/
##
## Made by Benoit Lormeau
## Login   <benoit.lormeau@epitech.eu>
##
## Started on  Fri Oct 14 08:52:27 2016 Benoit Lormeau
## Last update Thu Dec 22 15:32:37 2016 Benoit Lormeau
##

SRC	=	in_array.c		\
		lowercase.c		\
		numeric.c		\
		my_max.c		\
		my_min.c		\
		uppercase.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
