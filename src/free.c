/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:02:17 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/20 17:02:30 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_img(t_img *img)
{
	if (img->img_ptr)
		free(img->img_ptr);
	if (img->draw_map)
		free(img->draw_map);
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		if (mlx->main_img)
			free_img(mlx->main_img);
		if (mlx->main_img)
			free_img(mlx->menu_img);
		free(mlx->mlx_ptr);
	}
}

void	process_cleaning(t_fdf *fdf)
{
	t_mlx	*mlx;
	int		i;

	mlx = fdf->mlx;
	free(fdf->button_grad_y);
	i = 0;
	while (i < fdf->infos.y_max)
	{
		if (fdf->map[i])
			free(fdf->map[i]);
		if (fdf->original_map)
			free(fdf->original_map[i]);
		i++;
	}
	if (fdf->map)
		free(fdf->map);
	if (fdf->original_map)
		free(fdf->original_map);
	fdf->mlx = 0x0;
}
