#include "../include/and_goodbye.h"

char	*chrstr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if (c == 0)
		return ((char *)(&s[i]));
	return (NULL);
}

char	*line_fd(char *saved)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		dest[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		dest[i] = saved[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*saved_fd(char *saved)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	line = (char *)malloc(sizeof(char) * (strlen(saved) - i + 1));
	if (!line)
		return (NULL);
	i++;
	while (saved[i])
		line[j++] = saved[i++];
	line[j] = '\0';
	free(saved);
	return (line);
}

char	*strjoin(char *s1, char *s2)
{
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	char*	dest = malloc(sizeof(char) * (strlen(s1) + (strlen(s2) + 1)));
	if (!dest)
		return (NULL);
	size_t	i = -1;
	size_t	j = 0;
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[j])
		dest[i++] = s2[j++];
	dest[strlen(s1) + strlen(s2)] = '\0';
	free (s1);
	return (dest);
}

char	*read_fd(const int fd, char *saved)
{
	char *buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	int bytes = 1;
	while (bytes > 0 && !chrstr(saved, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		if (!saved)
		{
			saved = malloc(1 * sizeof(char));
			*saved = '\0';
		}
		saved = strjoin(saved, buff);
	}
	free(buff);
	return (saved);
}

char	*keep_reading_fd(int fd)
{
	static char	*saved;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	saved = read_fd(fd, saved);
	if (!saved)
		return (NULL);
	buff = line_fd(saved);
	saved = saved_fd(saved);
	return (buff);
}