/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjerdnap <tjerdnap@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:31:07 by tjerdnap          #+#    #+#             */
/*   Updated: 2024/03/16 17:17:59 by tjerdnap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*left_char[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(left_char[fd]);
		buffer = NULL;
		left_char[fd] = NULL;
		return (0);
	}
	line = next_line_break(fd, left_char[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_char[fd] = store_line(line);
	return (line);
}

// int	main(void)
// {
// 	int fd1;
// 	int	fd2;
// 	char *line;
// 	int num_line;

// 	num_line = 1;
// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	while ((line = get_next_line(fd1)))
// 	{
// 		printf("File 1, Line %d: %s", num_line++, line);
// 		free(line);
// 	}
// 	printf("\n");
// 	num_line = 1;
// 	while ((line = get_next_line(fd2)))
// 	{
// 		printf("File 2, Line %d: %s", num_line++, line);
// 		free(line);
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return(0);
// }
