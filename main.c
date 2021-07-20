/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:37:05 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/20 21:07:06 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		initialise_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->size_x = 1000;
	mlx->size_y = 400;
	mlx->win = mlx_new_window(mlx->mlx_ptr, mlx->size_x, mlx->size_y, "fdf");
	mlx_key_hook(mlx->win, keys_action, mlx);
}

void		test(t_mlx *mlx)
{
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

	draw_bressman_line(mlx, x0, x1, y0, y1);
}


int main(int argc, const char *argv[])
{
	t_mlx	mlx;
	t_map	map;
	t_fdf	fdf;

	if (argc != 2)
	{
		printf("Usage: ./fdf filename\n");
		return 1;
	}
	initialise_mlx(&mlx);
	fdf.mlx = &mlx;
	parsing_map(&fdf, argv[1]);
	draw_origin(&fdf);
	link_point(&fdf);
	//test(&mlx);
	mlx_loop(mlx.mlx_ptr);

	return 0;
}
