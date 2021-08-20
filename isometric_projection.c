/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:15:20 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/20 15:15:22 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    transform_isometric_point(t_point *p)
{
    float previous_x;
    float previous_y;

    previous_x = p->x;
    previous_y = p->y;
    p->x = (previous_x - previous_y) * cos(0.523599);
    p->y = - p->z + (previous_x + previous_y) * sin(0.523599);
    //printf("ISO (%2f, %2f) to (%2f, %2f)\n", previous_x, previous_y, p->x, p->y);
}

void    transform_isometric_map(t_fdf *fdf)
{
    int     i;
    int     j;

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