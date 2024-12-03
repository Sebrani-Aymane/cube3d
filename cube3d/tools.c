/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:29:46 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/02 04:23:42 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strlenn(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
char *ft_del_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (&str[i]);
}

int	ft_strncmp(char *s1, char *s2, int	n)
{
	int	i;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i] && s2[i] && s1[i])
		i++;
	return ((s1[i]) - (s2[i]));
}
char *ft_strtrim(char  *s1, char  *set)
{
    int start;
    int end;
    char *trimmed;

    if (!s1 || !set)
        return (NULL);

    start = 0;
    while (s1[start] && ft_strchr(set, s1[start]))
        start++;
    end = ft_strlenn(s1);
    while (end > start && ft_strchrr(set, s1[end - 1]))
        end--;
    trimmed = malloc((end - start + 1) * sizeof(char));
    if (!trimmed)
        return (NULL);
    strlcpy(trimmed, s1 + start, end - start + 1);

    return (trimmed);
}
char *ft_strchrr(char *s, int c)
{
    char char_to_find = ( char)c;

    while (*s != '\0')
    {

        if (*s == char_to_find)
            return ((char *)s);
        s++;
    }
    if (char_to_find == '\0')
        return ((char *)s);
    return (NULL);
}