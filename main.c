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

int main(int argc, const char *argv[])
{
	t_mlx	mlx;
	t_fdf	fdf;
	t_img	menu_img;
	t_img	main_img;

	if (argc != 2)
	{
		printf("Usage: ./fdf filename\n");
		initialise_fdf(&fdf, &mlx, &main_img, &menu_img);
		parsing_map(&fdf, "maps/42.fdf");
		//return 1;
	}
	else
	{
		initialise_fdf(&fdf, &mlx, &main_img, &menu_img);
		parsing_map(&fdf, argv[1]);
	}
	printf("parsing finis\n");
	mlx_key_hook(mlx.win, keys_action, &fdf);
	mlx_mouse_hook(mlx.win, mouse_event, &fdf);
	process_draw(&fdf);
	mlx_loop(mlx.mlx_ptr);
	return 0;
}
