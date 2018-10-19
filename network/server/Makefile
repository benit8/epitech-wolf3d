##
## Makefile for SFML_tests in /home/benito/Misc/SFML
##
## Made by Benoit Lormeau
## Login   <benoit.lormeau@epitech.net>
##
## Started on  Sun Nov 27 17:34:15 2016 Benoit Lormeau
## Last update Fri Jan  6 14:19:53 2017 Benoit Lormeau
##

CFLAGS	+=	-Iinclude/
CFLAGS	+=	-Wall -Wextra
CFLAGS	+=	-g3

LDFLAGS	+=	-lm
LDFLAGS	+=	-lcsfml-graphics
LDFLAGS	+=	-lcsfml-network
LDFLAGS	+=	-lcsfml-system

RM	=	rm -f

SRC	=	src/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	server

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re