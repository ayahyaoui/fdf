/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 20:56:29 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/25 21:38:55 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



void		initialise_mlx(t_mlx *mlx)
{
	int bits_per_pixel;
	int size_line;
	int endian;

	bits_per_pixel = 0; size_line = 0; endian = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->size_y = 1350; // TODO adapter la taille selon l'ecran
	mlx->size_x = mlx->size_y * 3 / 2;//2150;
	mlx->width_menu = mlx->size_x / 4;
	mlx->win = mlx_new_window(mlx->mlx_ptr, mlx->size_x + mlx->width_menu, mlx->size_y, "fdf");

	mlx->img_map = mlx_new_image(mlx->mlx_ptr, mlx->size_x, mlx->size_y);
	mlx->draw_map = mlx_get_data_addr(mlx->img_map, &bits_per_pixel,
			   &(mlx->size_line), &endian);

	mlx->img_menu = mlx_new_image(mlx->mlx_ptr, mlx->width_menu, mlx->size_y);
	mlx->draw_menu = mlx_get_data_addr(mlx->img_menu, &bits_per_pixel,
			   &(mlx->size_line_menu), &endian);
	printf("bits_per_pixel %d size_line %d endian %d\n",
			bits_per_pixel, size_line, endian);
}



void		initialise_fdf(t_fdf *fdf, t_mlx * mlx)
{
	bzero(fdf, sizeof(t_fdf));
	initialise_mlx(mlx);
	fdf->mlx = mlx;
	fdf->infos.zoom = 1;
	fdf->infos.zoom_pas = 1;
	fdf->infos.zoom_x = 3; // Ratio 3 / 2
	fdf->infos.zoom_y = 2;
	fdf->infos.deep_pas = 2;
	fdf->infos.deep = 1;
	fdf->angle.pas = 10;
}

