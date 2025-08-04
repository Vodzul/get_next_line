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
	byte = read(fd, buffer, BUFFER_SIZE);
	if (byte <= 0)
	{
		free(buffer);
		if (byte < 0 || *stash == '\0')
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
	int		start;
	char	*temp;
	char	*line;
	char	*stash;

	stash = *stashptr;
	i = 0;
	start = i;
	while (stash[i] != '\n' && stash[i] != '\0') // su an veri ustteki while dongusunden kesin var \n in indisini bul
		i++;
	line = ft_substr(stash, start, i + 1); // baslangictan /n'e kadar al ve bunu line'da tut
	if (!line)
		return (NULL);
	temp = stash;
	stash = ft_substr(temp, i + 1, ft_strlen(temp) - i); //stash'ten yazdirdigim kismi silmek icin \n e kadar olan kisma git ve orayi sil
	if (!stash)
		return (NULL);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	ssize_t		byte;
	char		*temp;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup(""); //stashte bir sey yoksa icine bisiler yazabilecegin bos string dondur
	if (!stash) // olusmazsa null dondur
		return (NULL);
	while (!ft_strchr(stash, '\n')) // stashte /n yoksa read ile biraz daha veri oku
	{
		stash = readline(fd, stash);
		if (!stash)
			return (NULL);
	}
	line = setline(&stash);
	return (line);
}
