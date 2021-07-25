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
	mlx->size_x = 2500;
	mlx->size_y = 1200;
	mlx->win = mlx_new_window(mlx->mlx_ptr, mlx->size_x, mlx->size_y, "fdf");
	mlx->img = mlx_new_image(mlx->mlx_ptr, mlx->size_x, mlx->size_y);

	mlx->draw_map = mlx_get_data_addr(mlx->img, &bits_per_pixel,
			   &(mlx->size_line), &endian);
	printf("bits_per_pixel %d size_line %d endian %d\n",
			bits_per_pixel, size_line, endian);
}



void		initialise_fdf(t_fdf *fdf, t_mlx * mlx)
{
	bzero(fdf, sizeof(t_fdf));
	initialise_mlx(mlx);
	fdf->mlx = mlx;


}


