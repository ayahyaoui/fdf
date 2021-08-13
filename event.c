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
		fdf->x_origin -= fdf->zoom;
	else if (key == LEFT)
		fdf->x_origin += fdf->zoom;
	else if (key == UP)
		fdf->y_origin += fdf->zoom;
	else if (key == DOWN)
		fdf->y_origin -= fdf->zoom;
	else
		return (-1);
	//printf("bouge\n");
	process_draw(fdf);
	return (1);
}

int			keys_action(int key, void *param)
{
	t_fdf	*fdf;
	t_mlx	*mlx;

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
	if (key == ZOOM)
		fdf->zoom += 10;
	
	if (key == X_RIGHT || key == X_LEFT)
		rotateX(fdf, key == X_RIGHT ? 1 : -1);
	if (key == Y_RIGHT || key == Y_LEFT)
		rotateY(fdf, key == Y_RIGHT ? 1 : -1);
	if (key == Z_RIGHT || key == Z_LEFT)
		rotateZ(fdf, key == Z_RIGHT ? 1 : -1);		
	return 1;
}


int			test_event2(int keycode, void *param)
{
	t_mlx *var;

	var = param;
	printf("code events 02 (press0) vallue: %d\n", keycode);
	
	if (keycode == 12)
	{
		mlx_destroy_window(var->mlx_ptr, var->win);
		free(var);
		exit(0);
	}
	return 1;
}





