#include <fcntl.h>   // open()
#include <unistd.h>  // close()
#include <stdio.h>   // printf()
#include <stdlib.h>  // free()
#include "get_next_line.h"

static char	*trim_stash2(char *stash, size_t i)
{
	size_t	j;
	char	*new_stash;

	new_stash = malloc((ft_strlen(stash) - i) + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
	{
		new_stash[j] = stash[i];
		i++;
		j++;
	}
	new_stash[j] = '\0';
	return (new_stash);
}

char	*trim_stash(char *stash)
{
	size_t		i;
	char		*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = trim_stash2(stash, i);
	return (new_stash);
}

int	has_newline(char *stash)
{
	int	i;

	if(!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	while (!has_newline(stash) && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		stash = join_and_free(stash, buffer);
	}
	if (!stash || *stash == '\0')
		return (NULL);
	line = extract_line(stash);
	stash = trim_stash(stash);
	return (line);
}

int main(void)
{
    int     fd;
    char    *line;

    fd = open("get_next_line.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (1);
    }

    // 1行ずつ読み出して出力
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // メモリ解放を忘れずに
    }

    close(fd);
    return (0);
}