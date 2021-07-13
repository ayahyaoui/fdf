/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:37:05 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/13 18:42:08 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		f_noevent()
{
	printf("aucun evenement\n");
	while(1);
	return (0);
}


int		test_event1()
{
	printf("code events 01\n");
	return 1;
}


int		test_event2(int keycode, void *param)
{
	t_mlx *var;

	var = param;
	printf("code events 02 (press0) vallue: %d\n", keycode);
	
	if (keycode == 12)
	{
		mlx_destroy_window(var->mlx_ptr, var->win);
		free(var);
		exit(0);
	}
	return 1;
}

int main(int argc, const char *argv[])
{
	t_mlx *mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();

	mlx->win = mlx_new_window(mlx->mlx_ptr, 1000, 400, "test_fdf");
	//printf("aucun evenement\n");
	mlx_hook(mlx->win, 2, (1L << 0), test_event2, mlx);
	mlx_loop(mlx->mlx_ptr);

	return 0;
}
