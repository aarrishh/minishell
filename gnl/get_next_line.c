/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:03:20 by mabaghda          #+#    #+#             */
/*   Updated: 2025/03/04 13:35:32 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *already_read, char *buf)
{
	ssize_t	bytes;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		else if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		already_read = ft_strjoin(already_read, buf);
		if (!already_read)
			return (NULL);
		if (ft_strchr(already_read, '\n'))
			break ;
	}
	return (already_read);
}

static char	*check_line(char *final_line)
{
	int		a;
	char	*cut;

	a = 0;
	while (final_line[a] != '\n' && final_line[a] != '\0')
		a++;
	if (final_line[a] == '\0' || final_line[a + 1] == '\0')
		return (NULL);
	cut = ft_substr(final_line, a + 1, ft_strlen(final_line) - a);
	if (!cut)
		return (NULL);
	final_line[a + 1] = '\0';
	return (cut);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*already_read;
	char		*final_line;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
	{
		free(buf);
		free(already_read);
		buf = NULL;
		already_read = NULL;
		return (NULL);
	}
	final_line = read_line(fd, already_read, buf);
	free(buf);
	buf = NULL;
	if (!final_line || *final_line == '\0')
	{
		free(final_line);
		return (NULL);
	}
	already_read = check_line(final_line);
	return (final_line);
}

/*#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error opening file.\n", 20);
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
