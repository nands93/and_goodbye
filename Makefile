NAME	= and_goodbye

CC	= cc
RM	= /bin/rm -f
AR	= ar rcs
RANLIB = ranlib
CFLAGS = -I/usr/include/SDL2
LDFLAGS = -L/usr/lib -lSDL2
SDLFLAGS	=	`sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

SRC	= config.c utils.c read_fd.c split_string.c render.c image.c validator.c infected_map.c and_goodbye.c

OBJS	= $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(SDLFLAGS)
			printf "COMPILATION SUCCESSFUL!\n"

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)
		printf "FULLY CLEANED!\n"

re:	fclean all

.SILENT:

.PHONY: all clean fclean re
