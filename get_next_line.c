/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjerdnap <tjerdnap@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:14:34 by tjerdnap          #+#    #+#             */
/*   Updated: 2024/03/16 17:17:49 by tjerdnap         ###   ########.fr       */
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

static char	*next_line_break(int fd, char *left_char, char *buffer)
{
	ssize_t	byte_read;
	char	*temp;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			return (NULL);
		}
		else if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		if (!left_char)
			left_char = ft_strdup("");
		temp = left_char;
		left_char = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_char);
}

static char	*store_line(char *line)
{
	char	*left_char;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	left_char = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*left_char == '\0')
	{
		free(left_char);
		left_char = NULL;
	}
	line[i + 1] = '\0';
	return (left_char);
}

char	*get_next_line(int fd)
{
	static char	*left_char;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(left_char);
		buffer = NULL;
		left_char = NULL;
		return (NULL);
	}
	line = next_line_break(fd, left_char, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_char = store_line(line);
	return (line);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	int num_line;

// 	num_line = 1;
// 	fd = open("test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%d: %s\n", num_line++, line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }