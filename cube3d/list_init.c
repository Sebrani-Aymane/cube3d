/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:54:45 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/25 19:13:50 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_map_infos(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
	{
		if (sp[i] == '0')
			return (0);
		i++;
	}
	return (1);
}

t_list *node_init(char *line)
{
	char	**s;

	s = ft_split(line, ' ');
	if (s[0][0] >= '0' && s[0][0] <= '9')
		parse_map_infos(s);
}

t_list *init_list(char *line)
{
	t_list	*node;

	node = malloc(sizeof(t_list*));
	if (!node)
		return (NULL);
	node = node_init(node);
}