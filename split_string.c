#include "and_goodbye.h"

char	*substring(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	size_t	len_s = strlen((char *)s);
	size_t	len_d = len_s - start;
	if (start > len_s)
		return (strdup(""));
	if (len_d >= len)
		dest = malloc(sizeof(char) * (len + 1));
	else
		dest = malloc(sizeof(char) * (len_d + 1));
	if (!dest)
		return (NULL);
	strncpy(dest, &s[start], (len + 1));
	dest[len + 1] = '\0';
	return (dest);
}

static int	count_words(const char *s, char c)
{
	int	i = 0;
	int	isword = 0;
	while (*s)
	{
		if (*s != c && isword == 0)
		{
			isword = 1;
			i++;
		}
		else if (*s == c)
			isword = 0;
		s++;
	}
	return (i);
}

static char	size_word(char const *s, char c, int i)
{
	int	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

char	**split_string(char const *s, char c)
{
	int i = 0;
	int j = 0;
	if (!s)
		return (NULL);
	int counter = count_words((char *)s, c);
	char** str = (char **)malloc((counter + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (j < counter)
	{
		while (s[i] == c)
			i++;
		int size = size_word(s, c, i);
		str[j] = substring(s, i, size);
		j++;
		i += size;
	}
	str[j] = 0;
	return (str);
}