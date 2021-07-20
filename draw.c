/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:16:25 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/20 21:07:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_outline(t_fdf *fdf, int x, int y,int size, int color)
{
	for (int i = -2; i < size; i++) 
		for (int j = -2; j < size ;j ++)
			mlx_pixel_put(fdf->mlx->mlx_ptr, fdf->mlx->win, x + i, y + j, color);
}



// prerequis x1 >= x0
void		draw_bressman_line(t_mlx *mlx, int x0, int x1, int y0, int y1)
{
	int		d2x;
	int		d2y;
	int		erreur;
	int		diff_y;

	diff_y = (y0 < y1) ? 1 : -1;
	d2x = 2 * (x1 - x0);
	d2y = 2 * (y1 - y0);
	erreur = (x1 - x0) * diff_y;

	while(x0 < x1)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win, x0, y0, set_b(0, 255));
		erreur -= (d2y * diff_y) ;
		while (erreur <= 0) // descendre ou monter
		{
			y0+= diff_y;
			erreur += d2x ;
		}
		x0++;
	}
	if (ft_abs(y0 - y1) > 1)
		printf("arrive %d vs %d diff_y %d\n", y0, y1, diff_y);
}



void		link_point(t_fdf *fdf)
{
	int			x;
	int			y;
	t_point		*first_point;
	t_point		*second_point;


	y = 0;
	while (y < fdf->y_max)
	{
		x = 0;
		while (x < fdf->x_max)
		{
			if (x > 0)
			{
				first_point = &(fdf->map[y][x - 1]);
				second_point = &(fdf->map[y][x]);
				draw_bressman_line(fdf->mlx, first_point->x, second_point->x,
						first_point->y, second_point->y);
			}
			if (y > 0 && x > 0)
			{
				first_point = &(fdf->map[y - 1][x - 1]);
				second_point = &(fdf->map[y][x]);
				draw_bressman_line(fdf->mlx, first_point->x, second_point->x,
						first_point->y, second_point->y);
			}
			x++;
		}
		y++;
	}
}

void		draw_origin(t_fdf *fdf)
{
	int			i;
	int			j;
	t_point		*point;

	i = 0;
	while (i < fdf->y_max)
	{
		j = 0;
		while (j < fdf->x_max)
		{
			point = &(fdf->map[i][j]);
			draw_outline(fdf, point->x, point->y, 2, set_g(0, 255));
			j++;
		}
		i++;
	}

}




