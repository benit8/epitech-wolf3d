##
## Makefile for wolf3d in /home/benito/delivery/wolf3d
## 
## Made by Benoit Lormeau
## Login   <benoit.lormeau@epitech.eu>
## 
## Started on  Tue Dec 13 10:15:32 2016 Benoit Lormeau
## Last update Tue Dec 13 10:16:12 2016 Benoit Lormeau
##

CFLAGS	+=	-Iinclude/
CFLAGS	+=	-W -Wall

LDFLAGS	+=	-lm
LDFLAGS	+=	-lc_graph_prog

SRC	=	src/main.c		\
		src/angle.c		\
		src/audio.c		\
		src/inputs.c		\
		src/map.c		\
		src/move.c		\
		src/raycasting.c	\
		src/states.c	\
		src/ui.c		\
		src/utils.c		\
		src/framebuffer.c	\
		src/my_put_pixel.c	\
		src/my_draw_line.c	\
		src/my_put_square.c

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
