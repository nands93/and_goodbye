#include "and_goodbye.h"

char	**render_map(t_game *render, const char *path)
{
	const int	fd = open(path, O_RDONLY);
	if (fd < 0)
		game_error("ERROR: FILE NOT FOUND");
	while (1)
	{
		render->buffer = keep_reading_fd(fd);
		if (render->buffer == NULL)
			break ;
		render->map = strjoin(render->map, render->buffer);
		free(render->buffer);
	}
	close(fd);
	if (render->map == NULL)
		game_error("ERROR: EMPTY MAP");
	return (split_string(render->map, '\n'));
}

int	draw_map(t_game *game)
{
	int x = 0;
	while (game->render[x])
	{
		int y = 0;
		while (game->render[x][y])
		{
			translate_map(game, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
