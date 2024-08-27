#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_keycode.h>
# include <SDL2/SDL_image.h>

# define IMG_SIZE 32
# define BUFFER_SIZE 42
# define TREE "./img/environment/tree.xpm"
# define FLOOR "./img/environment/floor.xpm"
# define ITEM "./img/environment/collectable.xpm"
# define EXIT "./img/environment/exit.xpm"
# define CHAR "./img/character/idle_front.xpm"
# define CHAR_BACK "./img/character/idle_back.xpm"
# define CHAR_LEFT "./img/character/idle_left.xpm"
# define CHAR_RIGHT "./img/character/idle_right.xpm"

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
}	t_player;

typedef struct s_map
{
	int		height;
	int		width;
	int		player;
	int		item;
	int		exit;
	int		infected_exit;
	int		infected_item;
}	t_map;

typedef struct s_game
{
	SDL_Window*		window;
	SDL_Renderer*	renderer;
	SDL_Surface*	screenSurface;
	char**			render;
	char**			infected_map;
	char*			buffer;
	char*			map;
	int				collect;
	int				finish;
	int				hei;
	int				wid;
	int				px;
	int				py;
	void*			sdl;
	void*			player;
	void*			tree;
	void*			floor;
	void*			exit;
	void*			item;
	t_player		config;
	t_map			counter;
}	t_game;

//render.c
char	**render_map(t_game *game, const char *path);
int		draw_map(t_game *game);

//utils.c
void	putchar_fd(const char c, const int fd);
void	putstr_fd(char *s, const int fd);
void	putend(char *s, const int fd);
int		game_error(char	*msg);
int		game_success(char	*msg);
void	render_free(char **render);
void	check_ber(const char *find);

//read_fd.c
char	*strjoin(char *s1, char *s2);
char	*line_fd(char *saved);
char	*saved_fd(char *saved);
char	*read_fd(const int fd, char *saved);
char	*keep_reading_fd(int fd);

//split_string.c
char		*substring(char const *s, unsigned int start, size_t len);
static int	count_words(const char *s, char c);
static char	size_word(char const *s, char c, int i);
char		**split_string(char const *s, char c);

//config.c
void	config(t_game *game);
void	close_game(t_game *game);
void	initializator(t_game *game);
void	map_counter(t_game *game);
int		counter_error(t_game *game);

//validator.c
int		check_validation(t_game *game);

//image.c
void	*image(t_game *game, char *path);
void	sprites(t_game *game, void *img, int x, int y);
void	translate_map(t_game *game, const int x, const int y);
void	change_image(t_game *game, char *new_image);
int		*img_init(t_game *game);

//movement.c
void	deal_key(const SDL_Keycode keycode, t_game *game);

//infection.c
void	translate_infect_map(t_game *game, int x, int y);
int		draw_infection_map(t_game *game);
void	infection_checker(t_game *game, int x, int y);

#endif