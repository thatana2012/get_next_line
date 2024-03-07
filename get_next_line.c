/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjerdnap <tjerdnap@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:14:34 by tjerdnap          #+#    #+#             */
/*   Updated: 2024/03/07 15:59:01 by tjerdnap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	else
		return (NULL);
}

static char	*fill_line(int fd, char *c_rest, char *buffer)
{
	ssize_t	byte_read;
	char	*temp;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(c_rest);
			return (NULL);
		}
		else if (byte_read == 0)
			break ;
		buffer[byte_read] = 0;
		if (!c_rest)
			c_rest = ft_strdup("");
		temp = c_rest;
		c_rest = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (c_rest);
}

static char	*polish_line(char *line_buffer)
{
	char	*c_rest;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	c_rest = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*c_rest == 0)
	{
		free(c_rest);
		c_rest = NULL;
	}
	line_buffer[i + 1] = 0;
	return (c_rest);
}

char	*get_next_line(int fd)
{
	static char	*c_rest;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(c_rest);
		buffer = NULL;
		c_rest = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line(fd, c_rest, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	c_rest = polish_line(line);
	return (line);
}

#include <stdio.h>

int	main(void)
{
	int fd;
	char *line;
	int num_line;

	num_line = 1;
	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
		printf("%d: %s\n", num_line++, line);
}