NAME = and_goodbye

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
    WINFLAGS = -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
else
    RM = rm -f
    EXE_EXT =
	LDFLAGS = -lSDL2 -lSDL2_image
endif


DEBUG_FLAGS = -g3

SRC = config.c utils.c read_fd.c split_string.c render.c image.c validator.c infected_map.c and_goodbye.c movement.c
OBJS = $(SRC:.c=.o)

%.o: %.c
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