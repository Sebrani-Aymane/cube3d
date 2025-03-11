/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:18:51 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/11 02:32:59 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	res = c_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1),1);
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}

char	*ft_strchr(char *string, int c )
{
	char	*str;

	if (!string)
		return (NULL);
	str = (char *)string;
	while (*str != c && *str != 0)
		str++;
	if (*str == c)
		return (str);
	else
		return (NULL);
}

void	ft_bzero(void *s, int n)
{
	char	*str;
	int	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(int count, int size)
{
	char	*res;

	res = c_malloc(size * count,1);
	if (!res)
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
}
