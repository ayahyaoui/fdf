/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:38:15 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/20 19:59:32 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keys_action(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (key == QUIT || key == ESC)
	{
		printf("Merci.\n");
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		free(mlx->mlx_ptr); 
		//free(mlx);
		exit(0);
	}
	return 1;
}


int		test_event2(int keycode, void *param)
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





