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

t_img	*initialise_img(t_img *img, int width, void *mlx_ptr)
{
	int	bits_per_pixel;
	int	endian;

	ft_bzero(img, sizeof(t_img));
	img->height = SIZE_HEIGHT;
	img->width = width;
	img->img_ptr = mlx_new_image(mlx_ptr, img->width, img->height);
	img->draw_map = mlx_get_data_addr(img->img_ptr, &bits_per_pixel,
			&(img->size_line), &endian);
	return (img);
}

	/*
	mlx->size_y = SIZE_HEIGHT; // TODO adapter la taille selon l'ecran
	mlx->size_x = mlx->size_y * 3 / 2;//2150;
	mlx->width_menu = mlx->size_x / 4;
	

	mlx->img_map = mlx_new_image(mlx->mlx_ptr, mlx->size_x, mlx->size_y);
	mlx->draw_map = mlx_get_data_addr(mlx->img_map, &bits_per_pixel,
			   &(mlx->size_line), &endian);

	mlx->img_menu = mlx_new_image(mlx->mlx_ptr, mlx->width_menu, mlx->size_y);
	mlx->draw_menu = mlx_get_data_addr(mlx->img_menu, &bits_per_pixel,
			   &(mlx->size_line_menu), &endian);
	printf("bits_per_pixel %d size_line %d endian %d\n",
			bits_per_pixel, size_line, endian);
	*/
t_mlx	*initialise_mlx(t_mlx *mlx, t_img *main, t_img *menu)
{
	mlx->mlx_ptr = mlx_init();
	main = initialise_img(main, SIZE_HEIGHT * 3 / 2, mlx->mlx_ptr);
	menu = initialise_img(menu, main->width / 4, mlx->mlx_ptr);
	mlx->win = mlx_new_window(mlx->mlx_ptr, main->width + menu->width,
			SIZE_HEIGHT, "FDF");
	mlx->main_img = main;
	mlx->menu_img = menu;
	return (mlx);
}

void	initialise_fdf(t_fdf *fdf, t_mlx *mlx, t_img *main, t_img *menu)
{
	ft_bzero(fdf, sizeof(t_fdf));
	mlx = initialise_mlx(mlx, main, menu);
	fdf->mlx = mlx;
	fdf->infos.zoom = 1;
	fdf->infos.zoom_pas = 1;
	fdf->infos.zoom_x = 3;
	fdf->infos.zoom_y = 2;
	fdf->infos.deep_pas = 2;
	fdf->infos.deep = 1;
	fdf->infos.step_size = 10;
	fdf->angle.pas = 10;
	fdf->type_projection = PARALLELE;
}
