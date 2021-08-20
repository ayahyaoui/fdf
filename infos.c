/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:01:16 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/19 16:01:19 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ZOOM_STEP_MIN 1
#define ZOOM_STEP_MAX 10
#define DEPTH_STEP_MIN 1
#define DEPTH_STEP_MAX 10
#define MOVE_STEP_MIN 1
#define MOVE_STEP_MAX SIZE_HEIGHT
#define ROTATION_STEP_MIN 1
#define ROTATION_STEP_MAX 120
#define DEBUG 0

double	get_proportion(t_fdf *fdf, t_option type_infos)
{
	double	value;

	if (type_infos == MOVE_STEP)
	{
		value = (fdf->infos.step_size * fdf->infos.zoom
				* fdf->infos.zoom_y - MOVE_STEP_MIN);
		return (value / (MOVE_STEP_MAX - MOVE_STEP_MIN));
	}
	if (type_infos == ZOOM_STEP)
	{
		value = fdf->infos.zoom_pas - ZOOM_STEP_MIN;
		return (value / (ZOOM_STEP_MAX - ZOOM_STEP_MIN));
	}
	if (type_infos == DEPTH_STEP)
		return ((double)(fdf->infos.deep_pas - DEPTH_STEP_MIN)
			/ (DEPTH_STEP_MAX - DEPTH_STEP_MIN));
	if (type_infos == ROTATION_STEP)
		return ((double)(fdf->angle.pas - ROTATION_STEP_MIN)
			/ (ROTATION_STEP_MAX - ROTATION_STEP_MIN));
	return (0.5);
}

t_point	get_pixel_center(t_fdf *fdf)
{
	t_point	center;
	int		middle;

	middle = fdf->infos.y_max / 2;
	center.x = (fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x
			* fdf->infos.zoom * fdf->infos.zoom_x) - (fdf->infos.x_origin
			* fdf->infos.zoom * fdf->infos.zoom_x);
	center.y = (fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y
			* fdf->infos.zoom * fdf->infos.zoom_y) - (fdf->infos.y_origin
			* fdf->infos.zoom * fdf->infos.zoom_y);
	center.z = 0;
	return (center);
}

void	display_fdfinfos(t_fdf *fdf)
{
	t_mlx	*mlx;
	t_infos	*infos;
	t_img	*main_img;
	t_img	*menu_img;

	mlx = fdf->mlx;
	infos = &(fdf->infos);
	main_img = mlx->main_img;
	menu_img = mlx->menu_img;
	printf("Infos:\n dimension map (%d, %d)\n", infos->x_max, infos->y_max);
	printf("original pos (%.2f, %.2f)\n", infos->x_origin, infos->y_origin);
	printf("main img (w, h, s_l)(%d, %d, %d)\n", main_img->width, main_img->height, main_img->size_line);
	printf("menu img (w, h, s_l)(%d, %d, %d)\n", menu_img->width, menu_img->height, menu_img->size_line);
	if (!menu_img->img_ptr || !menu_img->draw_map || !main_img->img_ptr || !main_img->draw_map)
		printf(" Issue with (main or menu) img null pointer\n");
	else
		printf("main img and menu_img seems fine\n");
	if (!mlx->win || !mlx->mlx_ptr)
		printf("Issue with (mlx or window) null pointer\n");
	else
		printf("mlx ptr seems fine\n");
	printf("zoom map (%d, %d)\n", infos->zoom, infos->zoom_pas);
	printf("depth map (%d, %.2f)\n", infos->deep, infos->deep_pas);
	printf("Rotation: (x, y, z, step) (%d, %d, %d, %d)\n", fdf->angle.x, fdf->angle.y, fdf->angle.z, fdf->angle.pas);
	if (fdf->type_projection == PARALLELE)
		printf("The projection is PARALLELE\n");
	if (fdf->type_projection == ISOMETRIC)
		printf("The projection is ISOMETRIC\n");
	if (fdf->type_projection == CONIQUE)
		printf("The projection is CONIQUE\n");
	if (fdf->type_projection == ORTHO)
		printf("The projection is ORTHO\n");
	if (DEBUG == 1)
		dislplay_map_infos(fdf);
}
