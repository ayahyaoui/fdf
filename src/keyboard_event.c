/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:38:15 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/21 17:06:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define SIZE_H SIZE_HEIGHT

int	process_key_direction(t_fdf *fdf, int key)
{
	int		direction;

	direction = 1;
	if (fdf->infos.x_max < 420 || fdf->infos.y_max < 420)
		direction = -1;
	if (key == RIGHT)
		fdf->infos.x_origin += fdf->infos.step_size * direction;
	else if (key == LEFT)
		fdf->infos.x_origin -= fdf->infos.step_size * direction;
	else if (key == UP)
		fdf->infos.y_origin -= fdf->infos.step_size * direction;
	else if (key == DOWN)
		fdf->infos.y_origin += fdf->infos.step_size * direction;
	else
		return (-1);
	process_draw(fdf);
	return (1);
}

int	process_rotation(t_fdf *fdf, int key)
{
	int				sens;
	t_type_rotation	type_rotation;

	fdf->angle.nb_rotate += 1;
	fdf->angle.nb_rotate %= 10;
	sens = -1;
	if (key == X_RIGHT || key == Y_RIGHT || key == Z_RIGHT)
		sens = 1;
	if (key == X_RIGHT || key == X_LEFT)
		fdf->angle.x += fdf->angle.pas * sens;
	if (key == Y_RIGHT || key == Y_LEFT)
		fdf->angle.y += fdf->angle.pas * sens;
	if (key == Z_RIGHT || key == Z_LEFT)
		fdf->angle.z += fdf->angle.pas * sens;
	type_rotation = ROTATION_X;
	if (key == Y_RIGHT || key == Y_LEFT)
		type_rotation = ROTATION_Y;
	if (key == Z_RIGHT || key == Z_LEFT)
		type_rotation = ROTATION_Z;
	if (!fdf->angle.nb_rotate % 2 || 1)
		rotate_precision(fdf);
	else
		rotate_direction(fdf, type_rotation, sens);
	return (1);
}

int	process_zoom(t_fdf *fdf, int key)
{
	t_point	center;
	t_point	new_center;
	int		*z;

	z = &fdf->infos.zoom;
	center = get_pixel_center(fdf);
	if (key == ZOOM && *z * fdf->infos.zoom_y * fdf->infos.step_size < SIZE_H)
	{
		fdf->infos.zoom += fdf->infos.zoom_pas;
		if (*z * fdf->infos.step_size > SIZE_HEIGHT)
			*z = SIZE_HEIGHT / (fdf->infos.zoom_y * fdf->infos.step_size);
		if (*z * fdf->infos.zoom_y * fdf->infos.step_size >= SIZE_HEIGHT - 2)
			fdf->infos.step_size = SIZE_HEIGHT / (fdf->infos.zoom_y * *z) - 1;
	}
	if (key == UNZOOM && (fdf->infos.zoom > fdf->infos.zoom_pas))
		fdf->infos.zoom -= fdf->infos.zoom_pas;
	else if (key == UNZOOM && (fdf->infos.zoom <= fdf->infos.zoom_pas))
		fdf->infos.zoom = 1;
	new_center = get_pixel_center(fdf);
	fdf->infos.x_origin -= (center.x - new_center.x) / (*z * fdf->infos.zoom_x);
	fdf->infos.y_origin -= (center.y - new_center.y) / (*z * fdf->infos.zoom_y);
	process_draw(fdf);
	return (1);
}

int	process_deep(t_fdf *fdf, int key)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->infos.y_max)
	{
		j = 1;
		while (j < fdf->map[i][0].x)
		{
			if (key == DEEPER)
				fdf->map[i][j].z += fdf->original_map[i][j].z;
			else
				fdf->map[i][j].z -= fdf->original_map[i][j].z;
			j++;
		}
		i++;
	}
	if (key == DEEPER)
		fdf->infos.deep += fdf->infos.deep_pas;
	else
		fdf->infos.deep -= fdf->infos.deep_pas;
	rotate_precision(fdf);
	return (1);
}

/*
 * 
 * 		//free(mlx);
 * ...
 * 
**/
int	keys_action(int key, void *param)
{
	t_fdf	*fdf;
	t_mlx	*mlx;

	fdf = (t_fdf *)param;
	mlx = fdf->mlx;
	if (key == QUIT || key == ESC)
	{
		process_cleaning(fdf);
		exit(0);
	}
	if (key == LEFT || key == RIGHT || key == UP || key == DOWN)
		return (process_key_direction(fdf, key));
	if (key == UNZOOM || key == ZOOM)
		return (process_zoom(fdf, key));
	if (key == INFOS)
		display_fdfinfos(fdf);
	if (key == X_RIGHT || key == X_LEFT || key == Y_RIGHT || key == Y_LEFT
		|| key == Z_RIGHT || key == Z_LEFT)
		return (process_rotation(fdf, key));
	if (key == SHALLOWER || key == DEEPER)
		process_deep(fdf, key);
	if (key == NEXT_PROJECTION)
		process_next_projection(fdf);
	return (1);
}
