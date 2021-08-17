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
		fdf->infos.x_origin -= fdf->infos.step_size;//fdf->infos.zoom;
	else if (key == LEFT)
		fdf->infos.x_origin += fdf->infos.step_size;//fdf->infos.zoom;
	else if (key == UP)
		fdf->infos.y_origin += fdf->infos.step_size;//fdf->infos.zoom;
	else if (key == DOWN)
		fdf->infos.y_origin -= fdf->infos.step_size;//fdf->infos.zoom;
	else
		return (-1);
	process_draw(fdf);
	return (1);
}

int 		process_rotation(t_fdf *fdf, int key)
{
	fdf->angle.nb_rotate += 1;
	fdf->angle.nb_rotate %= 10;
	if (key == X_RIGHT || key == X_LEFT)
		fdf->angle.x += (key == X_RIGHT) ? fdf->angle.pas : -fdf->angle.pas;
	if (key == Y_RIGHT || key == Y_LEFT)
		fdf->angle.y += (key == Y_RIGHT) ? fdf->angle.pas : -fdf->angle.pas;
	if (key == Z_RIGHT || key == Z_LEFT)
		fdf->angle.z += (key == Z_RIGHT) ? fdf->angle.pas : -fdf->angle.pas;
	if (!fdf->angle.nb_rotate)
		rotate_precision(fdf);
	else
		rotate_precision(fdf);
	
	return (1);
}

int			process_zoom(t_fdf *fdf, int key)
{
	t_point center;
    int     middle;
	double 	pos_x;
	double 	pos_y;

	middle = fdf->infos.y_max / 2;
    center.x = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x * fdf->infos.zoom * fdf->infos.zoom_x - (fdf->infos.x_origin * fdf->infos.zoom * fdf->infos.zoom_x);
    center.y = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y * fdf->infos.zoom * fdf->infos.zoom_y - (fdf->infos.y_origin * fdf->infos.zoom * fdf->infos.zoom_y);
	//printf("first point before %f %f %d\n", center.x, fdf->infos.x_origin * fdf->infos.zoom * fdf->infos.zoom_x, (int)(fdf->map[0][0].x * fdf->infos.zoom * fdf->infos.zoom_x - (fdf->infos.x_origin * fdf->infos.zoom * fdf->infos.zoom_x)));
	if (key == ZOOM && fdf->infos.zoom * fdf->infos.zoom_y * fdf->infos.step_size < SIZE_HEIGHT)
	{
		fdf->infos.zoom += fdf->infos.zoom_pas;
		if (fdf->infos.zoom * fdf->infos.zoom_y * fdf->infos.step_size> SIZE_HEIGHT)
			fdf->infos.zoom = SIZE_HEIGHT / (fdf->infos.zoom_y * fdf->infos.step_size);
		if (fdf->infos.zoom * fdf->infos.zoom_y * fdf->infos.step_size >= SIZE_HEIGHT -2)
			fdf->infos.step_size = SIZE_HEIGHT / (fdf->infos.zoom_y * fdf->infos.zoom) - 1;
		printf("zoom == %d step == %f total == %f\n", fdf->infos.zoom, fdf->infos.step_size, fdf->infos.zoom * fdf->infos.zoom_y * fdf->infos.step_size);
		process_draw(fdf);
	}
	if (key == UNZOOM )
	{
		if (fdf->infos.zoom <= fdf->infos.zoom_pas)
			fdf->infos.zoom = 1;
		else
			fdf->infos.zoom -= fdf->infos.zoom_pas;
		
		process_draw(fdf);
	}
	pos_x =  (fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x * fdf->infos.zoom * fdf->infos.zoom_x) - (fdf->infos.x_origin * fdf->infos.zoom * fdf->infos.zoom_x);
	pos_y =  (fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y * fdf->infos.zoom * fdf->infos.zoom_y) - (fdf->infos.y_origin * fdf->infos.zoom * fdf->infos.zoom_y);
	fdf->infos.x_origin -= (center.x - pos_x) /  (fdf->infos.zoom * fdf->infos.zoom_x);
	fdf->infos.y_origin -= (center.y - pos_y) /  (fdf->infos.zoom * fdf->infos.zoom_y);
	/*
	printf("first point after %f %f %d\n", fdf->map[0][0].x * fdf->infos.zoom * fdf->infos.zoom_x, fdf->infos.x_origin * fdf->infos.zoom * fdf->infos.zoom_x,
	 (int)(fdf->map[0][1].x * fdf->infos.zoom * fdf->infos.zoom_x - fdf->infos.x_origin * fdf->infos.zoom * fdf->infos.zoom_x));
	printf("old - new [%f]\n", (center.x - (fdf->map[0][0].x * fdf->infos.zoom * fdf->infos.zoom_x)));
	*/
	process_draw(fdf);
	return (1);
}

int 		process_deep(t_fdf *fdf, int key)
{
	int i;
	int j;
	
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
		free(fdf->button_grad_y);
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
	if (key == SHALLOWER || key == DEEPER)
		process_deep(fdf, key);
	return 1;
}