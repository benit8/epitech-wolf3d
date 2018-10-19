##
## Makefile for wolf3d in /home/benito/delivery/wolf3d
## 
## Made by Benoit Lormeau
## Login   <benoit.lormeau@epitech.eu>
## 
## Started on  Tue Dec 13 10:15:32 2016 Benoit Lormeau
## Last update Tue Jan 10 14:45:29 2017 Benoit Lormeau
##

CFLAGS	+=	-Iinclude/
CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	-g3

LDFLAGS	+=	-lm
LDFLAGS	+=	-lcsfml-audio
LDFLAGS	+=	-lcsfml-graphics
LDFLAGS	+=	-lcsfml-network
LDFLAGS	+=	-lcsfml-system
LDFLAGS	+=	-lcsfml-window
LDFLAGS	+=	-Llib/
LDFLAGS	+=	-lmy

SRC	=	src/main.c		\
		src/ai.c		\
		src/angle.c		\
		src/audio.c		\
		src/entities.c		\
		src/inputs.c		\
		src/game_objects.c	\
		src/network.c		\
		src/map.c		\
		src/move.c		\
		src/player.c		\
		src/raycast.c		\
		src/textures.c		\
		src/ui.c		\
		src/weapon.c		\
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

c:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LDFLAGS)

.PHONY: all clean fclean re
