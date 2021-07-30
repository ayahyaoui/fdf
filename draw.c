/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:16:25 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/25 21:58:04 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void		put_point_color(t_mlx *mlx, int x, int y, int color)
{
	//printf("point %d %d", x, y);
	if (y >= 0 && y < mlx->size_y && x >= 0 && x < mlx->size_x)
	{
		mlx->draw_map[y * mlx->size_line + x * 4 ] = (color) % 256;
		mlx->draw_map[y * mlx->size_line + x * 4 + 1] = (color >> 8) % 256;
		mlx->draw_map[y * mlx->size_line + x * 4 + 2] = (color >> 16) % 256;
		mlx->draw_map[y * mlx->size_line + x * 4+ 3] = (color >> 24) % 256;
	}
}


void		draw_outline(t_fdf *fdf, int x, int y,int size, int color)
{
	int pos_x;
	int pos_y;
	int i;
	int j;

	i = - size;
	while (i < size)
	{
		j = -size;
		while(j < size)
		{
			pos_x = x + j - fdf->x_origin;
			pos_y = y + i - fdf->y_origin;
			if (pos_y >= 0 && pos_y < fdf->mlx->size_y && pos_x >= 0 \
			&& pos_x < fdf->mlx->size_x)
				put_point_color(fdf->mlx, pos_x, pos_y, color);
			j++;
		}
		i++;
	}
}


int			draw_vertical_line(t_fdf *fdf, int x0, int x1, int y0, int y1)
{
	t_mlx		*mlx;

	mlx = fdf->mlx;
	if (y0 < y1)
		while(y0 < y1)
		{
			put_point_color(mlx, x0-  fdf->x_origin, y0 - fdf->y_origin, set_b(0, 255));
			y0++;
		}
	else
		while(y0 > y1)
		{
			put_point_color(mlx, x0 - fdf->x_origin, y0 - fdf->y_origin, set_b(0, 255));
			y0--;
		}
	return 1;
}


// prerequis x1 >= x0
int			draw_bressman_line(t_fdf *fdf, int x0, int x1, int y0, int y1)
{
	int		d2x;
	int		d2y;
	int		erreur;
	int		diff_y;
	t_mlx	*mlx;

	//printf("line %d %d %d %d\n", x0, x1, y0, y1);
	mlx = fdf->mlx;
	if (x0 == x1)
		return draw_vertical_line(fdf, x0, x1, y0, y1);
	if (x0 > x1)
		return draw_bressman_line(fdf, x1, x0, y1, y0);
	diff_y = (y0 < y1) ? 1 : -1;
	d2x = 2 * (x1 - x0);
	d2y = 2 * (y1 - y0);
	erreur = (x1 - x0) * diff_y;
	while(x0 < x1)
	{
		put_point_color(mlx, x0 - fdf->x_origin, y0 - fdf->y_origin, set_b(0, 255));
		//mlx_pixel_put(mlx->mlx_ptr, mlx->win, x0 + fdf->x_origin,
		//		y0 + fdf->y_origin, set_b(0, 255));
		erreur -= (d2y * diff_y) ;
		while (erreur <= 0) // descendre ou monter
		{
			y0+= diff_y;
			erreur += d2x ;
		}
		x0++;
	}
	if (ft_abs(y0 - y1) > 1)
		printf("arrive %d vs %d diff_y %d %lu\n", y0, y1, diff_y, ft_abs(y0-y1));
	return 1;
}


void		link_point(t_fdf *fdf)
{
	int			x;
	int			y;
	t_point		*first_point;
	t_point		*second_point;


	//printf("LINK %d\n", fdf->y_max);
	y = 0;
	while (y < fdf->y_max)
	{
		x = 1;
		//printf("%d / %d taille %d\n", y, fdf->y_max, fdf->map[y][0].x);
		while (x < fdf->map[y][0].x)
		{
			//printf("%d / %d\n", x, fdf->map[y][0].x);
			if (x > 1)
			{
				first_point = &(fdf->map[y][x - 1]);
				second_point = &(fdf->map[y][x]);
				draw_bressman_line(fdf, first_point->x, second_point->x,
						first_point->y, second_point->y);
			}
			if (y > 0 && x < fdf->map[y-1][0].x)
			{
				first_point = &(fdf->map[y - 1][x]);
				second_point = &(fdf->map[y][x]);
				draw_bressman_line(fdf, first_point->x, second_point->x,
						first_point->y, second_point->y);
			}
			x++;
		}
		y++;
	}
	//printf("END LINK\n");
}

void		draw_origin(t_fdf *fdf)
{
	int			i;
	int			j;
	t_point		*point;

	i = 0;


	while (i < fdf->y_max)
	{
		j = 1;
		
		while (j < fdf->map[i][0].x)
		{
			point = &(fdf->map[i][j]);
			draw_outline(fdf, point->x, point->y, 2, set_g(0, 255));
			j++;
		}
		i++;
	}
}


void        draw_menu(t_fdf *fdf);

void		process_draw(t_fdf *fdf){
	t_mlx	*mlx;
	mlx = fdf->mlx;
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win);
	bzero(mlx->draw_map, mlx->size_line * mlx->size_y);
	draw_menu(fdf);
	draw_origin(fdf);
	link_point(fdf);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_map, mlx->width_menu, 0);
	printf("fin process_draw\n");
}

void		process_isometric_projection(t_fdf *fdf){
	int y;
	int x;

	y = 0;
	printf("iso start\n");
	while (y < fdf->y_max)
	{
		x = 1;
		while (x < fdf->map[y][0].x)
		{
/*
			fdf->map[y][x].x = (int)((fdf->original_map[y][x].x -
					fdf->original_map[y][x].z) / ((double)sqrt(2)));
			fdf->map[y][x].y = (int)((fdf->original_map[y][x].x +
			2 * fdf->original_map[y][x].y + fdf->original_map[y][x].z) /
					((double)sqrt(6)));
*/
			double tmp_x = (double)((fdf->map[y][x].x -fdf->map[y][x].z) /
					((double)sqrt(2)));
			double tmp_y = (double)((fdf->map[y][x].x +2 * fdf->map[y][x].y +
					fdf->map[y][x].z) / ((double)sqrt(6)));
			//printf("%d->%f\n", fdf->map[y][x].x, tmp_x);
			fdf->map[y][x].y = (int)tmp_y;
			fdf->map[y][x].x = (int)tmp_x;

			x++;
		}
		y++;
	}
	printf("iso finsh\n");
}


void		change_projection(t_fdf *fdf, t_projection projection)
{
	if (projection == fdf->type_projection)
	{
		return;
	}
	if (projection == ISOMETRIC)
	{
		process_isometric_projection(fdf);
		process_draw(fdf);
		//dislplay_map_infos(fdf);
	}
}





