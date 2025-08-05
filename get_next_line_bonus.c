/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facelik <facelik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:29:25 by facelik           #+#    #+#             */
/*   Updated: 2025/08/05 02:56:56 by facelik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readline(int fd, char *stash)
{
	char	*buffer;
	ssize_t	byte;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byte = read(fd, buffer, BUFFER_SIZE);
	if (byte <= 0)
	{
		free(buffer);
		if (byte < 0 || *stash == '\0' || !stash)
		{
			free(stash);
			return (NULL);
		}
		return (stash);
	}
	buffer[byte] = '\0';
	temp = stash;
	stash = ft_strjoin(stash, buffer);
	free(temp);
	free(buffer);
	return (stash);
}

char	*setline(char **stashptr)
{
	int		i;
	char	*temp;
	char	*line;
	char	*stash;

	stash = *stashptr;
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	temp = ft_substr(stash, i, ft_strlen(stash) - i);
	if (!temp)
		return (NULL);
	free(*stashptr);
	*stashptr = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!stash[fd])
		return (NULL);
	while (!ft_strchr(stash[fd], '\n'))
	{
		stash[fd] = readline(fd, stash[fd]);
		if (!stash[fd])
			return (NULL);
	}
	line = setline(&stash[fd]);
	return (line);
}
