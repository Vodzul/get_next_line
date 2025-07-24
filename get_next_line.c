/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facelik <facelik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:29:25 by facelik           #+#    #+#             */
/*   Updated: 2025/07/24 06:37:59 by facelik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *buffer)
{
	int		i;
	char	*line;
	int		j;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*trim_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(ft_strlen(buffer) - i);
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		temp[BUFFER_SIZE + 1];
	ssize_t		bytes;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	while (!ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		temp[bytes] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(buffer, temp);
		free(tmp);
	}
	line = get_line(buffer);
	buffer = trim_buffer(buffer);
	return (line);
}
