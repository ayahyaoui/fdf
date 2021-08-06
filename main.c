/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:37:05 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/25 21:01:50 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void		test(t_fdf *fdf)
{
	int x0, y0;
	int x1, y1;
	t_mlx	*mlx;
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

	draw_bressman_line(fdf, x0, x1, y0, y1);
}

void		initialise_fdf(t_fdf *fdf, t_mlx *mlx);

int main(int argc, const char *argv[])
{
	t_mlx	mlx;
	t_map	map;
	t_fdf	fdf;

	if (argc != 2)
	{
		printf("Usage: ./fdf filename\n");
		initialise_fdf(&fdf, &mlx);
		parsing_map(&fdf, "maps/42.fdf");
		//return 1;
	}
	else
	{
		initialise_fdf(&fdf, &mlx);
		parsing_map(&fdf, argv[1]);
	}
	printf("parsing finis\n");
	mlx_key_hook(mlx.win, keys_action, &fdf);
	dislplay_map_infos(&fdf);
	process_draw(&fdf);
	dislplay_map_infos(&fdf);
	//test(&fdf);
	mlx_loop(mlx.mlx_ptr);

	return 0;
}
