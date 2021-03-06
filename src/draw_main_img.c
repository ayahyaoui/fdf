/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:27:10 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/18 22:27:11 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define COLORS_CENTER 1
#define THICKNESS 1

void	draw_outline(t_infos infos, t_img *img, t_point p, int size)
{
	int		pos_x;
	int		pos_y;
	int		i;
	int		j;

	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j < size)
		{
			pos_x = p.x + j - infos.x_origin * infos.zoom * infos.zoom_x;
			pos_y = p.y + i - infos.y_origin * infos.zoom * infos.zoom_y;
			if (pos_y >= 0 && pos_y < img->height && pos_x >= 0
				&& pos_x < img->width)
				put_point_color(img, pos_x, pos_y, p.color);
			j++;
		}
		i++;
	}
}

void	link_point(t_fdf *fdf, t_point first, t_point second)
{
	int			zoom_x;
	int			zoom_y;
	int			diff_y;

	zoom_x = fdf->infos.zoom * fdf->infos.zoom_x;
	zoom_y = fdf->infos.zoom * fdf->infos.zoom_y;
	first.x = (int)(first.x * zoom_x - fdf->infos.x_origin * zoom_x);
	first.y = (int)(first.y * zoom_y - fdf->infos.y_origin * zoom_y);
	second.x = (int)(second.x * zoom_x - fdf->infos.x_origin * zoom_x);
	second.y = (int)(second.y * zoom_y - fdf->infos.y_origin * zoom_y);
	diff_y = 1;
	if (first.y > second.y)
		diff_y = -1;
	if (first.color != second.color)
	{
		first.color = get_color_height(0);
		second.color = get_color_height(0);
	}	
	draw_bressman_line(fdf->mlx->main_img, first, second, diff_y);
}

void	link_points(t_fdf *fdf)
{
	int			x;
	int			y;

	y = 0;
	while (y < fdf->infos.y_max)
	{
		x = 1;
		while (x < fdf->map[y][0].x)
		{
			if (x > 1)
				link_point(fdf, fdf->map[y][x - 1], fdf->map[y][x]);
			if (y > 0 && x < fdf->map[y - 1][0].x)
				link_point(fdf, fdf->map[y - 1][x], fdf->map[y][x]);
			x++;
		}
		y++;
	}
}

/*
 *
 * else
 *	p.color = set_g(0, 255);
 * 
 * */
void	draw_origin(t_fdf *fdf)
{
	int			i;
	int			j;
	t_point		*point;
	t_point		p;

	i = 0;
	while (i < fdf->infos.y_max)
	{
		j = 1;
		while (j < fdf->map[i][0].x)
		{
			point = &(fdf->map[i][j]);
			p.x = point->x * fdf->infos.zoom * fdf->infos.zoom_x;
			p.y = point->y * fdf->infos.zoom * fdf->infos.zoom_y;
			point->color = get_color_height(fdf->original_map[i][j].z
					+ fdf->original_map[i][j].z * fdf->infos.deep);
			if (i == fdf->infos.y_max / 2 && (int)(fdf->map[i][0].x / 2) == j
				&& COLORS_CENTER)
				point->color = set_r(0, 255);
			p.color = point->color;
			draw_outline(fdf->infos, fdf->mlx->main_img, p, THICKNESS);
			j++;
		}
		i++;
	}
}

void	draw_main_img(t_fdf *fdf, t_img *img)
{
	bzero(img->draw_map, img->size_line * img->height);
	draw_origin(fdf);
	link_points(fdf);
}
