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

int			process_key_direction(t_fdf *fdf, int key)
{
	if (key == RIGHT)
		fdf->infos.x_origin -= 10;//fdf->infos.zoom;
	else if (key == LEFT)
		fdf->infos.x_origin += 10;//fdf->infos.zoom;
	else if (key == UP)
		fdf->infos.y_origin += 10;//fdf->infos.zoom;
	else if (key == DOWN)
		fdf->infos.y_origin -= 10;//fdf->infos.zoom;
	else
		return (-1);
	process_draw(fdf);
	return (1);
}

int 		process_rotation(t_fdf *fdf, int key)
{
	if (key == X_RIGHT || key == X_LEFT)
		fdf->angle.x += (key == X_RIGHT) ? fdf->angle.pas : -fdf->angle.pas;
	if (key == Y_RIGHT || key == Y_LEFT)
		fdf->angle.y += (key == Y_RIGHT) ? fdf->angle.pas : -fdf->angle.pas;
	if (key == Z_RIGHT || key == Z_LEFT)
		fdf->angle.z += (key == Z_RIGHT) ? fdf->angle.pas : -fdf->angle.pas;

	rotate_precision(fdf);
	return (1);
}

int			process_zoom(t_fdf *fdf, int key)
{
	if (key == ZOOM)
	{
		fdf->infos.zoom += fdf->infos.zoom_pas;
		process_draw(fdf);
	}
	if (key == UNZOOM && fdf->infos.zoom > fdf->infos.zoom_pas)
	{
		fdf->infos.zoom -= fdf->infos.zoom_pas;
		process_draw(fdf);
	}

	return (1);
}

int			keys_action(int key, void *param)
{
	t_fdf	*fdf;
	t_mlx	*mlx;
	int pas_zoom;

	fdf = (t_fdf*)param;
	mlx = fdf->mlx;
	if (key == QUIT || key == ESC)
	{
		printf("Merci.\n");
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		free(mlx->mlx_ptr); 
		//free(mlx);
		exit(0);
	}
	if (key == LEFT || key == RIGHT || key == UP || key == DOWN)
		return process_key_direction(fdf, key);
	if (key == UNZOOM || key == ZOOM)
		return process_zoom(fdf, key);
	if (key == INFOS)
		dislplay_map_infos(fdf);
	if (key == X_RIGHT || key == X_LEFT || key == Y_RIGHT || key == Y_LEFT || key == Z_RIGHT || key == Z_LEFT)
		return process_rotation(fdf, key);
	return 1;
}




