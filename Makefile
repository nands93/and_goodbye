NAME = and_goodbye

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
    WINFLAGS = -I\include\SDL2 -L\lib
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
else
    RM = rm -f
    EXE_EXT =
	LDFLAGS = -lSDL2 -lSDL2_image
endif

DEBUG_FLAGS = -g3

ifeq ($(OS),Windows_NT)
SRC = src\config.c \
	  src\utils.c \
	  src\read_fd.c \
	  src\split_string.c \
	  src\render.c \
	  src\image.c \
	  src\validator.c \
	  src\infected_map.c \
	  src\and_goodbye.c \
	  src\movement.c
else
SRC = src/config.c \
	  src/utils.c \
	  src/read_fd.c \
	  src/split_string.c \
	  src/render.c \
	  src/image.c \
	  src/validator.c \
	  src/infected_map.c \
	  src/and_goodbye.c \
	  src/movement.c
endif

OBJS = $(SRC:.c=.o)
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

ifeq ($(OS),Windows_NT)
$(NAME)$(EXE_EXT): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)$(EXE_EXT) $(WINFLAGS) $(LDFLAGS)
else
$(NAME)$(EXE_EXT): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)$(EXE_EXT) $(LDFLAGS)
endif

all: $(NAME)$(EXE_EXT)

ifeq ($(OS),Windows_NT)
debug: $(OBJS)
	$(CC) $(OBJS) $(DEBUG_FLAGS) -o $(NAME)$(EXE_EXT) $(WINFLAGS) $(LDFLAGS)
else
debug: $(OBJS)
	$(CC) $(OBJS) $(DEBUG_FLAGS) -o $(NAME)$(EXE_EXT) $(LDFLAGS)
endif

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)$(EXE_EXT)

re: fclean all

freshDebug: fclean debug

.SILENT:

.PHONY: all clean fclean re debug freshDebug