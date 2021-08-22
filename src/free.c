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

void	free_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		if (mlx->main_img)
			mlx_destroy_image(mlx->mlx_ptr, mlx->main_img->img_ptr);
		if (mlx->main_img)
			mlx_destroy_image(mlx->mlx_ptr, mlx->menu_img->img_ptr);
	}
}

void	process_cleaning(t_fdf *fdf)
{
	int		i;

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
	free_mlx(fdf->mlx);
}
