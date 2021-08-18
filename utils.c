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

t_point	*multiply_matrix_rotation(double mat[3][3], t_point *point)
{
	int		old_point[3];
	double	result[3];
	int		i;
	int		j;

	i = -1;
	old_point[0] = point->x;
	old_point[1] = point->y;
	old_point[2] = point->z;
	while (++i < 3)
		result[i] = 0.0;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			result[i] += mat[i][j] * old_point[j];
	}
	point->x = result[0];
	point->y = result[1];
	point->z = result[2];
	return (point);
}

void	dislplay_map_infos(t_fdf *map)
{
	int		i;
	int		j;

	if (map == 0x0)
	{
		printf("Error: dislplay_map_infos\n");
		return ;
	}
	printf("dimesion <%d, %d>\n", map->infos.x_max, map->infos.y_max);
	i = -1;
	while (++i < map->infos.y_max)
	{
		j = 0;
		while (++j < map->map[i][0].x)
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
