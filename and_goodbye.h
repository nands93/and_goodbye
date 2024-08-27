#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

# ifdef __linux__

enum	e_keycode
{
	UP = 119,
	DOWN = 115,
	LEFT = 97,
	RIGHT = 100,
	KEY_ESC = 65307
};
# else

enum	e_keycode
{
	UP = 13,
	DOWN = 1,
	LEFT = 0,
	RIGHT = 2,
	KEY_ESC = 53
};
# endif

# define SDL_ERROR 1
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
	SDL_Window* window;
	SDL_Renderer* renderer;
	char		**render;
	char		**infected_map;
	char		*buffer;
	char		*map;
	int			collect;
	int			finish;
	int			hei;
	int			wid;
	int			px;
	int			py;
	void		*sdl;
	// void		*win;
	void		*player;
	void		*tree;
	void		*floor;
	void		*exit;
	void		*item;
	t_player	config;
	t_map		counter;
}	t_game;

//render.c
char	**render_map(t_game *game, const char *path);
int		draw_map(t_game *game);

//utils.c
void	putchar_fd(const char c, const int fd);
void	putstr_fd(char *s, const int fd);
void	putendl(char *s, const int fd);
int		game_error(char	*msg);
int		game_sucess(char	*msg);
void	render_free(char **render);
void	check_ber(const char *find);

//read_fd.c
char	*strjoin(char *s1, char *s2);
char	*ft_chrstr(char *s, int c);
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
int		close_game(const t_game *game);
void	initializator(t_game *game);
void	map_counter(t_game *game);
int		counter_error(t_game *game);

//validator.c
void	format_checker(char **render);
void	walls_checker(const t_game *game);
void	char_checker(char **map);
int		check_validation(t_game *game);

//image.c
void	*image(t_game *game, char *path);
void	sprites(t_game *game, void *img, int x, int y);
void	translate_map(t_game *game, const int x, const int y);
void	put_layout(char **map, t_game *game);
void	change_image(t_game *game, char *new_image);
int		*img_init(t_game *game);

//movement.c
void	deal_key(int keycode, t_game *game);
int		key_hook(int keycode, t_game *game);

//infection.c
void	translate_infect_map(t_game *game, int x, int y);
int		draw_infection_map(t_game *game);
void	infection_checker(t_game *game, int x, int y);

#endif