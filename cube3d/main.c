/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:43 by asebrani          #+#    #+#             */
/*   Updated: 2024/11/25 17:51:29 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int ac, char **av)
{
	if (ac != 2 || !av[1])
		return (write(2,"Invalid arguments\n", 18), 0);
	if (!parse_map_name(av[1]))
		return(write(2, "invalid map name\n", 18), 0);
	if (!parse_map(av[1]))
		return(write(2, "invalid map\n", 18), 0);
	return(printf("all good\n"), 1);
}