#include <fcntl.h>   // open()
#include <unistd.h>  // close()
#include <stdio.h>   // printf()
#include <stdlib.h>  // free()
#include "get_next_line.h"

size_t	ft_strlen(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i])
		i++;
	return (i);
}

static char	*only_buffer(char *buffer)
{
	size_t	i;
	char	*new_str;

	new_str = malloc(ft_strlen(buffer) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		new_str[i] = buffer[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	*join_stash_buffer(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	new_str = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		new_str[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		new_str[i + j] = buffer[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

char	*join_and_free(char *stash, char *buffer)
{
	char	*new_str;

	if (!stash && !buffer)
		return (NULL);
	if (!stash)
		new_str = only_buffer(buffer);
	else
		new_str = join_stash_buffer(stash, buffer);
	free(stash);
	return (new_str);
}