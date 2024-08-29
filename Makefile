NAME	= and_goodbye

CC	= gcc
RM	= rm -f

LDFLAGS = -lSDL2 -lSDL2_image

DEBUG_FLAGS = -g3

SRC	= config.c utils.c read_fd.c split_string.c render.c image.c validator.c infected_map.c and_goodbye.c movement.c

OBJS	= $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
			printf "COMPILATION SUCCESSFUL!\n"

all:	$(NAME)

debug: 	$(OBJS)
		$(CC) $(OBJS) $(DEBUG_FLAGS) -o $(NAME) $(LDFLAGS)
		printf "SUCCESSFUL DEBUG!\n"

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)
		printf "FULLY CLEANED!\n"

re:	fclean all

freshDebug: fclean debug

.SILENT:

.PHONY: all clean fclean re
