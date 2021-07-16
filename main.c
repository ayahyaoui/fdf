/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:37:05 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/16 22:29:47 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		f_noevent()
{
	printf("aucun evenement\n");
	while(1);
	return (0);
}


int		test_event1()
{
	printf("code events 01\n");
	return 1;
}


int		keys_action(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (key == QUIT || key == ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		free(mlx);
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

t_map		*parsing_map(t_map *map, const char *file_name);
void	plot(int x, int y);
int set_r(int trgb, int r);


// prerequis x1 >= x0
void		bressman_line(t_mlx *mlx, int x0, int x1, int y0, int y1)
{
	int		d2x;
	int		d2y;
	int		erreur;
	int		diff_y;

	diff_y = (y0 < y1) ? 1 : -1;
	d2x = 2 * (x1 - x0);
	d2y = 2 * (y1 - y0);
	erreur = (x1 - x0) * diff_y;

	while(x0 < x1)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win, x0, y0, set_b(0, 255));
		erreur -= (d2y * diff_y) ;
		while (erreur <= 0) // descendre ou monter
		{
			y0+= diff_y;
			erreur += d2x ;
		}
		x0++;
	}
	if (ft_abs(y0 - y1) > 1)
		printf("arrive %d vs %d diff_y %d\n", y0, y1, diff_y);
}



int main(int argc, const char *argv[])
{
	t_mlx	*mlx;
	t_map	map;

	if (argc != 2)
	{
		printf("Usage: ./fdf filename\n");
		return 1;
	}
	parsing_map(&map, argv[1]);
	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, 1000, 400, "fdf");
	mlx_key_hook(mlx->win, keys_action, mlx);
	//printf("aucun evenement\n");
	
	int x0, y0;
	int x1, y1;
	x0 = 500;
	y0 = 200;

	x1 = 600;
	y1 = 50;
	for (int i = -2; i < 2; i++) {
		for (int j = -2; j < 2 ;j ++)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win, 
					x0 + i, y0 + j, set_g(0, 255));
			mlx_pixel_put(mlx->mlx_ptr, mlx->win, 
					x1 + i, y1 + j, set_r(0, 255));
		}
	}
	mlx_pixel_put(mlx->mlx_ptr, mlx->win, x0 - 1, y0, set_b(0, 255));

	bressman_line(mlx, x0, x1, y0, y1);

	mlx_loop(mlx->mlx_ptr);

	return 0;
}
