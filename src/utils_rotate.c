/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 17:24:44 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/22 17:24:46 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	create_point(int a, int b, int c)
{
	t_point	p;

	p.x = a;
	p.y = b;
	p.z = c;
	return (p);
}

void	copy_point(t_point *p1, t_point p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
	p1->z = p2.z;
	p1->color = p2.color;
}

void	center_not_move(t_fdf *fdf, t_point old_pos, t_point pos)
{
	fdf->infos.x_origin -= old_pos.x - pos.x;
	fdf->infos.y_origin -= old_pos.y - pos.y;
}

t_point	copy_center_map(t_fdf *fdf, t_point **map)
{
	t_point	center;
	int		middle;

	middle = fdf->infos.y_max / 2;
	center.x = map[middle][(int)(map[middle][0].x / 2)].x;
	center.y = map[middle][(int)(map[middle][0].x / 2)].y;
	return (center);
}

/*
 *
 * BONUS Optimistation
 * TODOOOOOOOOO
 * 
*/
void	rotate_direction(t_fdf *fdf, t_type_rotation direction, int sens)
{
	int		i;
	int		j;
	t_point	center;
	int		middle;

	middle = fdf->infos.y_max / 2;
	center.x = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x;
	center.y = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y;
	i = 0;
	while (i < fdf->infos.y_max)
	{
		j = 0;
		while (++j < fdf->map[i][0].x)
			rotate_point(&fdf->map[i][j], (M_PI * fdf->angle.pas / 120 * sens),
				direction);
		i++;
	}
	fdf->infos.x_origin -= center.x - fdf->map[middle]
	[(int)(fdf->map[middle][0].x / 2)].x;
	fdf->infos.y_origin -= center.y - fdf->map[middle]
	[(int)(fdf->map[middle][0].x / 2)].y;
	process_draw(fdf);
}
