/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:31:43 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/18 22:31:44 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define PLUS_BUTTON_NAME "plusbutton.xpm" // A CHANGER
#define MINUS_BUTTON_NAME "minusbutton.xpm"

/*
		gray background
		do alsoo cleaning
*/
void	draw_menu_background(t_img *img)
{
	int		i;
	int		j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->size_line)
		{
			img->draw_map[i * img->size_line + j] = 127;
			j++;
		}
		i++;
	}
}

/**
 * void	put_point_menu_color(t_mlx *mlx, int x, int y, int color)
{
	if (y >= 0 && y < mlx->size_y && x >= 0 && x < mlx->width_menu)
	{
		mlx->draw_menu[y * mlx->size_line_menu + x * 4 ] = (color) % 256;
		mlx->draw_menu[y * mlx->size_line_menu + x * 4 + 1] = (color >> 8) % 256;
		mlx->draw_menu[y * mlx->size_line_menu + x * 4 + 2] = (color >> 16) % 256;
		mlx->draw_menu[y * mlx->size_line_menu + x * 4+ 3] = (color >> 24) % 256;
	}
}
**/
int	put_subtitle(t_fdf *fdf, const char title[], int y, t_option option)
{
	int		color;
	t_mlx	*mlx;

	mlx = fdf->mlx;
	color = set_r(0, 255);
	if ((option == PROJECTION_ORTHO && fdf->type_projection == ORTHO)
		|| (option == PROJECTION_ISOMETRIC && fdf->type_projection == ISOMETRIC)
		|| (option == PROJECTION_PARALLELE
			&& fdf->type_projection == PARALLELE))
		color = set_g(0, 255);
	mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->menu_img->width / 4,
		y, color, (char*)title);
	return (1);
}

int	put_title(t_fdf *fdf, const char title[], int y, int color)
{
	t_mlx	*mlx;

	mlx = fdf->mlx;
	mlx_string_put(mlx->mlx_ptr, mlx->win,
		mlx->menu_img->width / 5, y, color, (char *)title);
	return (1);
}

void	draw_option(t_fdf *fdf, const t_menu type[], char name[GRID_NB][20],
				const t_option options[])
{
	int		i;
	t_mlx	*mlx;
	t_img	*img;

	i = 0;
	mlx = fdf->mlx;
	img = mlx->menu_img;
	while (i < GRID_NB)
	{
		if (type[i] == TITLE)
			put_title(fdf, name[i], i * mlx->menu_img->height / GRID_SIZE,
				set_b(0, 255));
		if (type[i] == SUB_TITLE)
			put_subtitle(fdf, name[i], i * mlx->menu_img->height / GRID_SIZE,
				options[i]);
		if (type[i] == GRADUATION)
		{
			put_graduation(fdf, name[i], name[i + 1],
				i * mlx->menu_img->height / GRID_SIZE);
			i++;
		}
		i ++;
	}
}

void	draw_menu(t_fdf *fdf)
{
	t_mlx					*mlx;
	static const t_menu		type[GRID_NB] = {NOTHING, NOTHING, NOTHING, TITLE,
		SUB_TITLE, SUB_TITLE, SUB_TITLE, NOTHING, TITLE, GRADUATION, GRADUATION,
		TITLE, GRADUATION, GRADUATION, TITLE, GRADUATION, GRADUATION, TITLE,
		GRADUATION, GRADUATION};
	static char				name[GRID_NB][20] = {"", "", "", "PROJECTION",
		"ORTHO", "ISOMETRIC", "PARALLELE", "", "ZOOM", MINUS_BUTTON_NAME,
		PLUS_BUTTON_NAME, "DEPTH", MINUS_BUTTON_NAME, PLUS_BUTTON_NAME,
		"ROTATION_STEP", MINUS_BUTTON_NAME, PLUS_BUTTON_NAME, "MOVE_STEP",
		MINUS_BUTTON_NAME, PLUS_BUTTON_NAME};
	static const t_option	options[GRID_SIZE] = {EMPTY, EMPTY, EMPTY,
		PROJECTION_TYPE, PROJECTION_ORTHO, PROJECTION_ISOMETRIC,
		PROJECTION_PARALLELE, EMPTY, ZOOM_STEP, ZOOM_STEP, ZOOM_STEP,
		DEPTH_STEP,	DEPTH_STEP, DEPTH_STEP, ROTATION_STEP, ROTATION_STEP,
		ROTATION_STEP, MOVE_STEP, MOVE_STEP, MOVE_STEP};

	mlx = fdf->mlx;
	draw_menu_background(mlx->menu_img);
	draw_menu_graduation(fdf, mlx->menu_img, type, options);
	draw_option(fdf, type, name, options);
}
