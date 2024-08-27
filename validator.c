#include "and_goodbye.h"

void	remove_newline(char *str)
{
	const size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	format_checker(char **render)
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

void walls_checker(const t_game *game)
{
	int x = 0;
	int y = 0;
	const int row = (game->wid / IMG_SIZE) - 1;
	const int col = (game->hei / IMG_SIZE) - 1;

	// Verificar o conteúdo da matriz
	printf("row: %d, col: %d\n", row, col);

	// Verificar as paredes laterais
	while (x <= row)
	{
		if (game->render[x][0] != '1' || game->render[x][col] != '1')
		{
			printf("game->render[x][0]: %c\n", game->render[x][0]);
			printf("game->render[x][col]: %c\n", game->render[x][col]);
			game_error("Error\nMAP MUST BE SURROUNDED BY WALLS 1");
		}
		x++;
	}

	// Verificar as paredes superior e inferior
	while (y <= col)
	{
		if (game->render[0][y] != '1' || game->render[row][y] != '1')
			game_error("Error\nMAP MUST BE SURROUNDED BY WALLS 2");
		y++;
	}
	printf("Fim wall checker\n");
}


void	char_checker(char **map)
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

int	path_checker(t_game *game, int x, int y)
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
	printf("Passou wall chacker\n");
	counter_error(game);
	path_checker(game, game->config.x, game->config.y);
	return (1);
}
