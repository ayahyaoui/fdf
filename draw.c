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

/**
void		put_point_colors(t_mlx *mlx, int x, int y, int color)
{
	if (y >= 0 && y < mlx->size_y && x >= 0 && x < mlx->size_x)
	{
		mlx->draw_map[y * mlx->size_line + x * 4 ] = (color) % 256;
		mlx->draw_map[y * mlx->size_line + x * 4 + 1] = (color >> 8) % 256;
		mlx->draw_map[y * mlx->size_line + x * 4 + 2] = (color >> 16) % 256;
		mlx->draw_map[y * mlx->size_line + x * 4+ 3] = (color >> 24) % 256;
	}
}
*/
void	put_point_color(t_img *img, int x, int y, int color)
{
	if (y >= 0 && y < img->height && x >= 0 && x < img->width)
	{
		img->draw_map[y * img->size_line + x * 4 ] = (color) % 256;
		img->draw_map[y * img->size_line + x * 4 + 1] = (color >> 8) % 256;
		img->draw_map[y * img->size_line + x * 4 + 2] = (color >> 16) % 256;
		img->draw_map[y * img->size_line + x * 4 + 3] = (color >> 24) % 256;
	}
}

void	draw_vertical_line(t_img *img, t_point p0, t_point p1)
{
	while (p0.y != p1.y)
	{
		put_point_color(img, p0.x, p0.y, set_b(0, 255));
		if (p0.y < p1.y)
			p0.y++;
		else
			p0.y--;
	}
}

/**
 * 
 * prerequis p1.x >= x0
 *
 *  
 **/
void	draw_bressman_line(t_img *img, t_point p0, t_point p1)
{
	int		d2x;
	int		d2y;
	int		erreur;
	int		diff_y;

	if (p0.x > p1.x)
		return (draw_bressman_line(img, p1, p0));
	diff_y = 1;
	if (p0.y < p1.y)
		diff_y == -1;
	d2x = 2 * (p1.x - p0.x);
	d2y = 2 * (p1.y - p0.y);
	erreur = (p1.x - p0.x) * diff_y;
	while (p0.x < p1.x)
	{
		put_point_color(img, p0.x, p0.y, set_b(0, 255));
		erreur -= (d2y * diff_y);
		while (erreur <= 0)
		{
			put_point_color(img, p0.x, p0.y, set_b(0, 255));
			p0.y += diff_y;
			erreur += d2x ;
		}
		p0.x++;
	}
}

void	process_draw(t_fdf *fdf)
{
	t_mlx	*mlx;

	mlx = fdf->mlx;
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win);
	bzero(mlx->menu_img, mlx->menu_img->size_line * mlx->menu_img->height);
	draw_menu(fdf);
	draw_main_img(fdf, mlx->main_img);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->main_img->img_ptr,
		mlx->menu_img->width, 0);
}
