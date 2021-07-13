/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getcode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:52:35 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/13 21:43:10 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "specialkey.h"

#define NB_SPECIAL_KEYS 7

#define LEFT 123
#define RIGHT 124
#define DOWN 125
#define UP 126
#define ZOOM 69
#define UNZOOM 78
#define QUIT 12

const char		*messages[NB_SPECIAL_KEYS + 1] =  {
	"Appuie sur la fleche de gauche",
	"Appuie sur la fleche de droite",
	"Appuie sur la fleche du bas",
	"Appuie sur la fleche du haut",
	"Choisie le boutton ZOOM",
	"Choisie le boutton DEZOOM",
	"Choisie le boutton QUIT",
	0x0
	};

const char		*define_name[NB_SPECIAL_KEYS + 1] =  {"LEFT", "RIGHT", "DOWN",
										"UP", "ZOOM", "UNZOOM", "QUIT", 0x0};

t_specialkeys	*initialise_specialkeys()
{
	t_specialkeys	*res;

	res = (t_specialkeys*)malloc(sizeof(t_specialkeys));
	res->key_value = malloc(sizeof(int) * NB_SPECIAL_KEYS);

	res->mlx_ptr = mlx_init();
	res->size_x = 1000; // get largeur
	res->size_y = 400; // get hauteur
	res->win_ptr = mlx_new_window(res->mlx_ptr,
			res->size_x, res->size_y, "get_keys");
	return res;
}


int		get_keys(int key, void *param)
{
	static int compteur = 0;
	int i;
	t_specialkeys *data = param;

	data->key_value[compteur] = key;
	compteur++;
	if (compteur < NB_SPECIAL_KEYS)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 200, set_b(0, 255),
						(char*)messages[compteur]);
	}
	else
	{
		i = -1;
		printf("ajoute les lignes ci dessous dans le fichier fdf.h\n");
		while (++i < NB_SPECIAL_KEYS)
			printf("#define %s %d\n", define_name[i], data->key_value[i]);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->key_value);
		free(data);
		exit(0);
	}
	return 1;
}

int		check_constante()
{
	int i;

	i = -1;
	while (++i < NB_SPECIAL_KEYS && messages[i] && define_name[i]);

	printf("%s %s\n", messages[i], define_name[i]);
	if (i < NB_SPECIAL_KEYS || messages[i] || define_name[i])
	{
		printf("Erreur nombre de touches special (%d %d)\n",
				NB_SPECIAL_KEYS, i);
		return 0;
	}
	return 1;
}

int main(int argc, const char *argv[])
{
	t_specialkeys *mlx;

	if (!check_constante())
		return 1;
	mlx = initialise_specialkeys();
	mlx_key_hook(mlx->win_ptr, get_keys, mlx);
	printf("%s\n", messages[0]);
	printf("%d\n", set_trgb(0,0,0,255));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
			10, mlx->size_y / 2, set_trgb(128, 255,255, 255), (char*)messages[0]);
	mlx_loop(mlx->mlx_ptr);

	return 0;
}


