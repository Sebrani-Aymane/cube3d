/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooore.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:54:43 by asebrani          #+#    #+#             */
/*   Updated: 2024/12/02 04:16:42 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*str;
	
	if (!s1)
		return (NULL);
	i = -1;
	str = malloc(ft_strlenn(s1) + 1);
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlenn(s))
		return (ft_strdup(""));
	if (start + len > ft_strlenn(s))
		len = ft_strlenn(s) - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return ((void *)0);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int ft_strcmp(char *s1, char *s2)
{
    char *u1;
    char *u2;

    u1 = s1;
    u2 = s2;
	if(!s1 || !s2)
		return(-1);
    while (*u1 && *u2 && *u1 == *u2)
    {
        u1++;
        u2++;
    }
    return (*u1 - *u2);
}
int ft_strlcpy(char *dst, const char *src, int dstsize)
{
    int srclen;
    int i;

    srclen = 0;
    while (src[srclen] != '\0')
        srclen++;
    if (dstsize == 0)
        return (srclen);
    i = 0;
    while (i < dstsize - 1 && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (srclen);
}