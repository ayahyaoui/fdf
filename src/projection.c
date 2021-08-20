/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 19:16:28 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/20 19:16:32 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_isometric_point(t_point *p)
{
	float	previous_x;
	float	previous_y;

	previous_x = p->x;
	previous_y = p->y;
	p->x = (previous_x - previous_y) * cos(0.523599);
	p->y = -p->z + (previous_x + previous_y) * sin(0.523599);
}

void	transform_isometric_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->infos.y_max)
	{
		j = 1;
		while (j < fdf->map[i][0].x)
		{
			transform_isometric_point(&(fdf->map[i][j]));
			j++;
		}
		i++;
	}
}

int	process_next_projection(t_fdf *fdf)
{
	fdf->angle.x = 0;
	fdf->angle.y = 0;
	fdf->angle.z = 0;
	if (fdf->type_projection == ISOMETRIC)
	{
		fdf->type_projection = PARALLELE;
	}
	else if (fdf->type_projection == PARALLELE)
	{
		fdf->type_projection = ISOMETRIC;
	}
	else
	{
		fdf->type_projection = PARALLELE;
	}
	rotate_precision(fdf);
	return (1);
}
