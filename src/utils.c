#include "../include/and_goodbye.h"

void	putchar_fd(const char c, const int fd)
{
	write (fd, &c, 1);
}

void	putstr_fd(char *s, const int fd)
{
	if (!s) return;
	while (*s)
		putchar_fd(*s++, fd);
}

void	putend(char *s, const int fd)
{
	if (!s) return;
	putstr_fd(s, fd);
	putchar_fd('\n', fd);
}

int	game_error(char	*msg)
{
	putend(msg, 2);
	exit(EXIT_FAILURE);
}

int	game_success(char	*msg)
{
	printf("%s\n", msg);
	exit(EXIT_SUCCESS);
}

void	render_free(char **render)
{
	int i = 0;
	while (render[i])
	{
		free(render[i]);
		i++;
	}
	free(render);
}

static int	search_word(const char *str, char *find)
{
	int i = 0;
	while (find[i])
	{
		if (find[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	check_ber(const char *find)
{
	int i = 0;
	while (find[i] != '\0')
	{
		if (find[i] == '.')
		{
			if (search_word(&find[i], ".ber"))
				return ;
		}
		i++;
	}
	game_error("Error\nFILE TYPE IS NOT VALID");
}

