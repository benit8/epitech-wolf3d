##
## Makefile for wolf3d in /home/benito/delivery/wolf3d
## 
## Made by Benoit Lormeau
## Login   <benoit.lormeau@epitech.eu>
## 
## Started on  Thu Jan  5 14:22:21 2017 Benoit Lormeau
## Last update Thu Jan  5 14:27:27 2017 Benoit Lormeau
##

CFLAGS	+=	-Iinclude/

LDFLAGS	+=	-Iinclude/
LDFLAGS	+=	-lc_graph_prog
LDFLAGS	+=	-lm

RM	=	rm -f

SRC	=	src/main.c		\
		src/my_put_pixel.c	\
		src/my_draw_line.c	\
		src/move_forward.c	\
		src/raycast.c

OBJ	=	$(SRC:.c=.o)

NAME	=	wolf3d

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
