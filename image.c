#include "and_goodbye.h"

void *image(t_game *game, char *path)
{
	SDL_Surface *xpmSurface = IMG_Load(path);
	if (!xpmSurface) {
		printf("Not possible to load XPM image: %s\n", IMG_GetError());
		SDL_DestroyRenderer(game->renderer);
		SDL_DestroyWindow(game->window);
		SDL_Quit();
		return NULL;
	}
	SDL_Texture *img = SDL_CreateTextureFromSurface(game->renderer, xpmSurface);
	SDL_FreeSurface(xpmSurface);
	if (!img) {
		printf("Not possible to create texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(game->renderer);
		SDL_DestroyWindow(game->window);
		SDL_Quit();
		return NULL;
	}
	return img;
}

void sdl_put_image_to_window(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	int wid, hei;
	SDL_QueryTexture(texture, NULL, NULL, &wid, &hei);
	destRect.w = wid;
	destRect.h = hei;

	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

int	*img_init(t_game *game)
{
	game->player = image(game, CHAR);
	game->tree = image(game, TREE);
	game->floor = image(game, FLOOR);
	game->exit = image(game, EXIT);
	game->item = image(game, ITEM);
	return (0);
}

void	sprites(t_game *game, void *img, int x, int y)
{
	sdl_put_image_to_window(game->renderer, img, x, y);
}

void	translate_map(t_game *game, const int x, const int y)
{
	const int	height = y * IMG_SIZE;
	const int	width = x * IMG_SIZE;
	if (game->render[x][y] == '1')
		sprites(game, game->tree, height, width);
	if (game->render[x][y] == '0')
		sprites(game, game->floor, height, width);
	if (game->render[x][y] == 'E')
		sprites(game, game->exit, height, width);
	if (game->render[x][y] == 'C')
		sprites(game, game->item, height, width);
	if (game->render[x][y] == 'P')
	{
		game->config.x = x;
		game->config.y = y;
		sprites(game, game->player, y * IMG_SIZE, x * IMG_SIZE);
	}
}

void	change_image(t_game *game, char *new_image)
{
	SDL_DestroyTexture(game->player);
	game->player = image(game, new_image);
}
