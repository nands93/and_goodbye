#include "../include/and_goodbye.h"

static void	remove_newline(char *str)
{
	const size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

static void	format_checker(char **render)
{
	int i = 0;
	remove_newline(render[0]);
	const size_t col = strlen(render[0]);
	while (render[i])
	{
		remove_newline(render[i]);
		if (col != strlen(render[i]))
			game_error("Error\nMAP SHOULD BE A RECTANGLE");
		i++;
	}
}

static void walls_checker(const t_game *game)
{
	const int row = (game->hei / IMG_SIZE) - 1;
	const int col = (game->wid / IMG_SIZE) - 1;

	int x = 0;
	while (x <= row)
	{
		if (game->render[x][0] != '1' || game->render[x][col] != '1')
		{
			game_error("Error\nMAP MUST BE SURROUNDED BY WALLS 1");
		}
		x++;
	}
	int y = 0;
	while (y <= col)
	{
		if (game->render[0][y] != '1' || game->render[row][y] != '1')
			game_error("Error\nMAP MUST BE SURROUNDED BY WALLS 2");
		y++;
	}
}

static void	char_checker(char **map)
{
	int i = 0;
	while (map[i])
	{
		int j = 0;
		while (map[i][j])
		{
			if (!strchr("PEC01", map[i][j]))
				game_error("Error\nWRONG CHARACTER IN MAP");
			j++;
		}
		i++;
	}
}

static int	path_checker(t_game *game, int x, int y)
{
	infection_checker(game, x, y);
	if (game->counter.item != game->counter.infected_item)
		game_error("Error\nIS IMPOSSIBLE TO GET EVERY ITEM");
	if (game->counter.exit != game->counter.infected_exit)
		game_error("Error\nMAP HAS INACCESSIBLE EXIT");
	return (1);
}

int	check_validation(t_game *game)
{
	format_checker(game->render);
	char_checker(game->render);
	walls_checker(game);
	counter_error(game);
	path_checker(game, game->config.x, game->config.y);
	return (1);
}
