/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:38:04 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/20 21:07:13 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/includes/libft.h"
#define BUFFER_MAP  128
#define DIMESION 3





void	dislplay_map_infos(t_fdf *map)
{
	int		i;
	int		j;

	if (map == 0x0)
	{
		printf("Error: dislplay_map_infos\n");
		return ;
	}
	printf("dimesion <%d, %d>\n", map->x_max, map->y_max);
	i = -1;
	while (++i < map->y_max)
	{
		for (j = 1; j < map->map[i][0].x; j++)
		{
			if (DIMESION > 2)
				printf("<%3.2f,%3.2f,%3.2f> ", map->map[i][j].x,
					map->map[i][j].y, map->map[i][j].z);
			else
				printf("<%3.2f,%3.2f> ", map->map[i][j].x,
					map->map[i][j].y);
		}
		printf("\n");
	}
}