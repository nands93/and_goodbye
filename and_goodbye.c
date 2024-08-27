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
		game.infected_map = render_map(&game, argv[1]);
		if (!game.render) {
			return (0);
		}
		config(&game);
		if (!check_validation(&game)) {
			game_error("Error\nPROVIDE A VALID MAP");
		}
		if (game.window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_Quit();
			return 1;
		}
		draw_map(&game);
		SDL_Event e;
		int quit = 0;
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = 1;
				}
				else if (e.type == SDL_KEYDOWN) {
					deal_key(e.key.keysym.sym, &game);
				}
				else if (e.type == SDL_QUIT) {
					close_game(&game);
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