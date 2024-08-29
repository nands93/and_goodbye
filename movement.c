#include "and_goodbye.h"

static void	print_steps(t_game *game)
{
	game->config.moves++;
	printf("Steps: %d\n", game->config.moves);
}

static void	move_player(t_game *game, int x, int y)
{
	int px = game->config.x;
	int py = game->config.y;
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
		game_success("CONGRATULATION! YOU WON!");
	print_steps(game);
	draw_map(game);
}

void	deal_key(const SDL_Keycode keycode, t_game *game)
{
	switch (keycode) {
		case SDLK_UP:
		case SDLK_w:
			change_image(game, CHAR_BACK);
			move_player(game, game->config.x - 1, game->config.y);
			break;
		case SDLK_DOWN:
		case SDLK_s:
			change_image(game, CHAR);
			move_player(game, game->config.x + 1, game->config.y);
			break;
		case SDLK_LEFT:
		case SDLK_a:
			change_image(game, CHAR_LEFT);
			move_player(game, game->config.x, game->config.y - 1);
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			change_image(game, CHAR_RIGHT);
			move_player(game, game->config.x, game->config.y + 1);
			break;
		case SDLK_ESCAPE:
			close_game(game);
			break;
		default:
			break;
	}
}