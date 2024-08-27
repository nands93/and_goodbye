#include "and_goodbye.h"

static void	print_steps(t_game *game)
{
	game->config.moves++;
	printf("Steps: %d\n", game->config.moves);
}

static void	move_player(t_game	*game, int x, int y)
{
	int	px;
	int	py;

	px = game->config.x;
	py = game->config.y;
	if (game->render[x][y] == '1')
		return ;
	if (game->render[x][y] == 'E' && game->counter.item != 0)
		return ;
	if (game->render[x][y] == 'C')
		game->counter.item--;
	if (game->render[x][y] == 'E')
		game->finish = 1;
	game->config.x = x;
	game->config.y = y;
	game->render[px][py] = '0';
	game->render[x][y] = 'P';
	if (game->finish)
		game_sucess("CONGRATULATION! YOU WON!");
	print_steps(game);
	draw_map(game);
}

void	deal_key(int keycode, t_game *game)
{
	if (keycode == UP)
	{
		change_image(game, CHAR_BACK);
		move_player(game, game->config.x - 1, game->config.y);
	}
	if (keycode == DOWN)
	{
		change_image(game, CHAR);
		move_player(game, game->config.x + 1, game->config.y);
	}
	if (keycode == LEFT)
	{
		change_image(game, CHAR_LEFT);
		move_player(game, game->config.x, game->config.y - 1);
	}
	if (keycode == RIGHT)
	{
		change_image(game, CHAR_RIGHT);
		move_player(game, game->config.x, game->config.y + 1);
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (game->finish == 1)
		close_game(game);
	else
		deal_key(keycode, game);
	return (0);
}
