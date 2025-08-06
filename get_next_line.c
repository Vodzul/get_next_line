/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
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
	while (!ft_strchr(stash, '\n'))
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte <= 0)
		{
			if (!stash || *stash == '\0')
				return (free(buffer), free(stash), NULL);
			return (free(buffer), stash);
		}
		buffer[byte] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		if (!stash)
			return (free(buffer), NULL);
	}
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
		return (free(line), NULL);
	free(*stashptr);
	*stashptr = temp;
	if (**stashptr == '\0')
	{
		free(*stashptr);
		*stashptr = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	stash = readline(fd, stash);
	if (!stash)
		return (NULL);
	line = setline(&stash);
	return (line);
}
