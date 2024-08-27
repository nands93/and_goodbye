#include "and_goodbye.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 1;
		}
		initializator(&game);
		check_ber(argv[1]);
		game.render = render_map(&game, argv[1]);
		int i = 0;
		while (game.render[i])
			printf(game.render[i++]);
		printf("\n");
		game.infected_map = render_map(&game, argv[1]);
		if (!game.render) {
			return (0);
		}
		printf("Chega aqui 1\n");
		config(&game);
		if (!check_validation(&game)) {
			game_error("Error\nPROVIDE A VALID MAP");
		}
		printf("Chega aqui 2\n");
		if (game.window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_Quit();
			return 1;
		}
		printf("Chega aqui 3\n");
		draw_map(&game);
		SDL_Event e;
		int quit = 0;
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = 1;
				}
			}
			SDL_RenderPresent(game.renderer);
		}
		SDL_DestroyRenderer(game.renderer);
		SDL_DestroyWindow(game.window);
		SDL_Quit();
	} else {
		game_error("Error\nINVALID NUMBER OF ARGUMENTS");
	}
	return (0);
}
