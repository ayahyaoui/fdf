/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu_graduation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:09:21 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/18 18:09:23 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define GRAD_BACK_COL GRADUATION_BACKGROUND_COLOR

void	draw_graduation(t_fdf *fdf, int pos_y, int lim_y, t_option option)
{
	int		start_x;
	int		j;
	double	proportion;
	t_img	*img;

	img = fdf->mlx->menu_img;
	proportion = get_proportion(fdf, option);
	start_x = (int)((double)(BUTTON_LEFT_W + img->width / 20)*4);
	while (pos_y < lim_y)
	{
		j = 0;
		while (j < ((img->width * 8 / 3) - start_x) * proportion)
		{
			put_point_color(img, (start_x + j) / 4, pos_y,
				set_g(0, 255));
			j += 4;
		}
		while (j < (img->width * 8 / 3) - start_x)
		{
			put_point_color(img, (start_x + j) / 4, pos_y,
				GRAD_BACK_COL);
			j += 4;
		}
		pos_y++;
	}
}

void	draw_menu_graduation(t_fdf *fdf, t_img *img, const t_menu *type,
	const t_option options[])
{
	int	index;
	int	graduation_index;
	int	add_pos;

	graduation_index = 0;
	add_pos = 0;
	if (!fdf->button_grad_y)
		add_pos = 1;
	if (add_pos)
		fdf->button_grad_y = ft_memalloc(sizeof(int) * GRADUATION_SIZE);
	index = -1;
	while (++index < GRID_NB)
	{
		if (type[index] == GRADUATION)
		{
			if (add_pos)
				fdf->button_grad_y[graduation_index++] = index * img->height
					/ GRID_SIZE;
			draw_graduation(fdf, index * img->height / GRID_SIZE,
				(index + 1) * img->height / GRID_SIZE, options[index]);
			index++;
		}
	}
	mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->win,
		img->img_ptr, 0, 0);
}

int	put_graduation(t_fdf *fdf, char title_min[], char title_plus[], int y)
{
	static void		*minus = NULL;
	static void		*plus = NULL;
	t_mlx			*mlx;
	int				w;
	int				h;

	mlx = fdf->mlx;
	if (!minus || !plus)
	{
		plus = mlx_xpm_file_to_image(mlx->mlx_ptr, (char *)title_plus, &w, &h);
		minus = mlx_xpm_file_to_image(mlx->mlx_ptr, (char *)title_min, &w, &h);
	}
	if (!minus || !plus)
		printf("NOOOOOO CRASH image non trou %s, %s\n", title_plus, title_min);
	else
	{
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, plus,
			mlx->menu_img->width * 2 / 3, y - 10);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, minus,
			mlx->menu_img->width / 20, y);
	}
	return (1);
}
