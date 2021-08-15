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
			pos_x = x + j - fdf->infos.x_origin * fdf->infos.zoom * fdf->infos.zoom_x;
			pos_y = y + i - fdf->infos.y_origin * fdf->infos.zoom * fdf->infos.zoom_y;
			if (pos_y >= 0 && pos_y < fdf->mlx->size_y && pos_x >= 0 \
			&& pos_x < fdf->mlx->size_x)
				put_point_color(fdf->mlx, pos_x, pos_y, color);
			j++;
		}
		i++;
	}
}

/*
int			draw_vertical_line(t_fdf *fdf, int x0, int x1, int y0, int y1)
{
	t_mlx		*mlx;

	mlx = fdf->mlx;
	if (y0 < y1)
		while(y0 < y1)
		{
			put_point_color(mlx, x0-  fdf->infos.x_origin, y0 - fdf->infos.y_origin, set_b(0, 255));
			y0++;
		}
	else
		while(y0 > y1)
		{
			put_point_color(mlx, x0 - fdf->infos.x_origin, y0 - fdf->infos.y_origin, set_b(0, 255));
			y0--;
		}
	return 1;
}*/


// prerequis x1 >= x0
int			draw_bressman_line(t_fdf *fdf, int x0, int x1, int y0, int y1)
{
	int		d2x;
	int		d2y;
	int		erreur;
	int		diff_y;
	t_mlx	*mlx;


	mlx = fdf->mlx;
	if (x0 > x1)
		return draw_bressman_line(fdf, x1, x0, y1, y0);
	diff_y = (y0 < y1) ? 1 : -1;
	d2x = 2 * (x1 - x0);
	d2y = 2 * (y1 - y0);
	erreur = (x1 - x0) * diff_y;
	while(x0 < x1)
	{
		put_point_color(mlx, x0, y0, set_b(0, 255));
		erreur -= (d2y * diff_y) ;
		while (erreur <= 0) // descendre ou monter
		{
			put_point_color(mlx, x0 , y0 , set_b(0, 255));
			y0+= diff_y;
			erreur += d2x ;
		}
		x0++;
	}
	while(y0 != y1)
	{
		put_point_color(mlx, x0 , y0 , set_b(0, 255));
		if (y0 < y1)
			y0++;
		else
			y0--;
		
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
	int zoom_x;
	int zoom_y;

	zoom_x = fdf->infos.zoom * fdf->infos.zoom_x;
	zoom_y = fdf->infos.zoom * fdf->infos.zoom_y;
	y = 0;
	//printf("zoom value %d %d\n", zoom_x, zoom_y);
	while (y < fdf->infos.y_max)
	{
		x = 1;
		while (x < fdf->map[y][0].x)
		{
			if (x > 1)
			{
				first_point = &(fdf->map[y][x - 1]);
				second_point = &(fdf->map[y][x]);
				draw_bressman_line(fdf, first_point->x * zoom_x - fdf->infos.x_origin * zoom_x,
									second_point->x * zoom_x - fdf->infos.x_origin * zoom_x,
									first_point->y * zoom_y - fdf->infos.y_origin * zoom_y,
						 			second_point->y * zoom_y - fdf->infos.y_origin * zoom_y);

			}
			if (y > 0 && x < fdf->map[y-1][0].x)
			{
				first_point = &(fdf->map[y - 1][x]);
				second_point = &(fdf->map[y][x]);
				draw_bressman_line(fdf, first_point->x * zoom_x - fdf->infos.x_origin * zoom_x,
									second_point->x * zoom_x - fdf->infos.x_origin * zoom_x,
									first_point->y * zoom_y - fdf->infos.y_origin * zoom_y,
									second_point->y * zoom_y - fdf->infos.y_origin * zoom_y);
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
	while (i < fdf->infos.y_max)
	{
		j = 1;
		while (j < fdf->map[i][0].x)
		{
			point = &(fdf->map[i][j]);
			
			if (i == fdf->infos.y_max / 2 && (int)(fdf->map[i][0].x / 2) == j)
				draw_outline(fdf, point->x * fdf->infos.zoom * fdf->infos.zoom_x,
						point->y * fdf->infos.zoom * fdf->infos.zoom_y, 2, set_r(0, 255));
			else
				draw_outline(fdf, point->x * fdf->infos.zoom * fdf->infos.zoom_x,
						point->y * fdf->infos.zoom * fdf->infos.zoom_y, 2, set_g(0, 255));
			j++;
		}
		i++;
	}
}




void		process_draw(t_fdf *fdf){
	t_mlx	*mlx;
	mlx = fdf->mlx;
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win);
	bzero(mlx->draw_map, mlx->size_line * mlx->size_y);
	draw_menu(fdf);
	draw_origin(fdf);
	link_point(fdf);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_map, mlx->width_menu, 0);
	//rintf("fin process_draw\n");
}
