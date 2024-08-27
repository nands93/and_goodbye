#include "and_goodbye.h"

void	translate_infect_map(t_game *game, int x, int y)
{
	int	height = y * IMG_SIZE;
	int width = x * IMG_SIZE;
	if (game->infected_map[x][y] == '1')
		sprites(game, game->tree, height, width);
	if (game->infected_map[x][y] == '0')
		sprites(game, game->floor, height, width);
	if (game->infected_map[x][y] == 'E')
		sprites(game, game->exit, height, width);
	if (game->infected_map[x][y] == 'C')
		sprites(game, game->item, height, width);
	if (game->infected_map[x][y] == 'P')
	{
		game->config.x = x;
		game->config.y = y;
		sprites(game, game->player, y * IMG_SIZE, x * IMG_SIZE);
	}
}

int	draw_infection_map(t_game *game)
{
	int x = 0;
	while (game->infected_map[x])
	{
		int y = 0;
		while (game->infected_map[x][y])
		{
			translate_infect_map(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

void	infection_checker(t_game *game, int x, int y)
{
	if (game->infected_map[x][y] == '1')
		return ;
	if (game->infected_map[x][y] == 'C')
		game->counter.infected_item++;
	if (game->infected_map[x][y] == 'E')
		game->counter.infected_exit++;
	game->infected_map[x][y] = '1';
	infection_checker(game, x + 1, y);
	infection_checker(game, x - 1, y);
	infection_checker(game, x, y + 1);
	infection_checker(game, x, y - 1);
}