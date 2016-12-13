##
## Makefile for wolf3d in /home/benito/delivery/wolf3d
## 
## Made by Benoit Lormeau
## Login   <benoit.lormeau@epitech.eu>
## 
## Started on  Tue Dec 13 10:15:32 2016 Benoit Lormeau
## Last update Tue Dec 13 10:16:12 2016 Benoit Lormeau
##

CC	=	gcc

CFLAGS	+=	-Iinclude/
CFLAGS	+=	-W -Wall -Werror

LDFLAGS	+=	-Iinclude/
LDFLAGS	+=	-lm
LDFLAGS	+=	-lc_graph_prog

RM	=	rm -f

SRC	=	src/main.c		\
		src/angle.c		\
		src/utils.c		\
		src/map.c		\
		src/framebuffer.c	\
		src/my_put_pixel.c	\
		src/my_draw_line.c	\
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
