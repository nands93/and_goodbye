#include "and_goodbye.h"

int	main(int argc, char **argv)
{
	t_game		game;
	SDL_Event	e;
	
	if (argc == 2) 
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 1;
		}
		initializator(&game);
		check_ber(argv[1]);
		game.render = render_map(&game, argv[1]);
		game.infected_map = render_map(&game, argv[1]);
		if (!game.render || !game.infected_map)
			close_game(&game);
		config(&game);
		if (!check_validation(&game))
			game_error("Error\nPROVIDE A VALID MAP");
		draw_map(&game);
		while (!game.finish)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					close_game(&game);
				else if (e.type == SDL_KEYDOWN)
					deal_key(e.key.keysym.sym, &game);
				else if (e.type == SDL_QUIT)
					close_game(&game);
				else
					continue;
			}
			SDL_RenderPresent(game.renderer);
		}
		close_game(&game);
	}
	else
		game_error("Error\nINVALID NUMBER OF ARGUMENTS");
	return (0);
}