#include "../include/and_goodbye.h"

void	config(t_game *game)
{
	size_t	x = 0;
	while (game->render[x])
		x++;
	game->wid = ((strlen(game->render[0]) - 1) * IMG_SIZE);
	game->hei = (x * IMG_SIZE);
	game->window = SDL_CreateWindow("SO_LONG_AND_GOODBYE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->wid, game->hei, SDL_WINDOW_SHOWN);
	if (game->window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		close_game(game);
	}
	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
	game->screenSurface = SDL_GetWindowSurface(game->window);
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	img_init(game);
}

void	close_game(t_game *game)
{
	free(game->buffer);
	free(game->map);
	render_free(game->render);
	render_free(game->infected_map);
	SDL_DestroyTexture(game->player);
	SDL_DestroyTexture(game->tree);
	SDL_DestroyTexture(game->floor);
	SDL_DestroyTexture(game->item);
	SDL_DestroyTexture(game->exit);
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	game->finish = 1;
	SDL_Quit();
	exit(0);
}

void	initializator(t_game *game)
{
	game->window = NULL;
	game->renderer = NULL;
	game->screenSurface = NULL;
	game->map = NULL;
	game->counter.height = 0;
	game->counter.width = 0;
	game->counter.item = 0;
	game->counter.exit = 0;
	game->counter.player = 0;
	game->counter.infected_exit = 0;
	game->counter.infected_item = 0;
	game->buffer = NULL;
	game->render = NULL;
	game->infected_map = NULL;
	game->tree = NULL;
	game->floor = NULL;
	game->exit = NULL;
	game->item = NULL;
	game->player = NULL;
	game->config.x = 0;
	game->config.y = 0;
	game->config.moves = 0;
	game->finish = 0;
	game->collect = 0;
	game->hei = 0;
	game->wid = 0;
	game->px = 0;
	game->py = 0;
}

void	map_counter(t_game *game)
{
	int x = 0;
	while (game->render[x])
	{
		int y = 0;
		while (game->render[x][y])
		{
			if (game->render[x][y] == 'C')
				game->counter.item++;
			if (game->render[x][y] == 'E')
				game->counter.exit++;
			if (game->render[x][y] == 'P')
			{
				game->config.x = x;
				game->config.y = y;
				game->counter.player++;
			}
			y++;
		}
		x++;
	}
}

int	counter_error(t_game *game)
{
	map_counter(game);
	if (game->counter.exit != 1)
		game_error("Error\nMAP SHOULD HAVE 1 EXIT");
	if (game->counter.item < 1)
		game_error("Error\nMAP SHOULD HAVE AT LEAST 1 COLLECTABLE");
	if (game->counter.player > 1)
		game_error("Error\nMAP SHOULD HAVE ONLY 1 PLAYER");
	if (game->counter.player < 1)
		game_error("Error\nMAP SHOULD HAVE A PLAYER");
	return (1);
}
