/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:02:33 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/19 05:20:21 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_read_function(int fd, char *save)
{
	char		*buffer;
	int			nb;

	if (!save)
		save = ft_calloc(1, 1);
	buffer = c_malloc((int)BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	nb = 1;
	while (nb)
	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb == -1)
		{
			return (NULL);
		}
		buffer[nb] = '\0';
		save = ft_strjoin(save, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (save);
}

char	*ft_line(char *save)
{
	char	*line;
	int		count;
	int		j;

	count = 0;
	j = -1;
	if (!save[count])
		return (NULL);
	while (save[count] && save[count] != '\n')
		count++;
	if (save[count] == '\n')
		count++;
	line = ft_calloc(count + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (++j < count)
		line[j] = save[j];
	return (line);
}

char	*ft_rest(char *save)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (NULL);
	rest = ft_calloc((ft_strlen(save + i) + 1), sizeof(char));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		rest[j++] = save[i++];
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (save = NULL, NULL);
	save = ft_read_function(fd, save);
	if (!save)
		return (NULL);
	line = ft_line(save);
	save = ft_rest(save);
	return (line);
}
