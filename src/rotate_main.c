/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 17:31:04 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/22 17:31:06 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*	
fdf->infos.x_origin -= center.x - fdf->map[middle]
[(int)(fdf->map[middle][0].x / 2)].x;
fdf->infos.y_origin -= center.y - fdf->map[middle]
[(int)(fdf->map[middle][0].x / 2)].y;
*/
void	rotate_precision(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	*point;
	t_point	old_center;

	old_center = copy_center_map(fdf, fdf->map);
	i = 0;
	while (i < fdf->infos.y_max)
	{
		j = 1;
		while (j < fdf->map[i][0].x)
		{
			copy_point(&(fdf->map[i][j]), fdf->original_map[i][j]);
			fdf->map[i][j].z += fdf->original_map[i][j].z * fdf->infos.deep;
			point = &(fdf->map[i][j]);
			rotate_total_point(point, create_point(fdf->angle.x,
					fdf->angle.z, fdf->angle.y), M_PI / 120);
			j++;
		}
		i++;
	}
	if (fdf->type_projection == ISOMETRIC)
		transform_isometric_map(fdf);
	center_not_move(fdf, old_center, copy_center_map(fdf, fdf->map));
	process_draw(fdf);
}
