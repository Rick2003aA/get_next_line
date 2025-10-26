#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

int	has_newline(char *stash);
size_t	ft_strlen(char *stash);
char	*extract_line(char *stash);
char	*get_next_line(int fd);
char	*join_and_free(char *stash, char *buffer);
char	*trim_stash(char *stash);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif