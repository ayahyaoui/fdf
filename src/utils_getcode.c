/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getcode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:52:35 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/16 22:29:51 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "specialkey.h"

#define NB_SPECIAL_KEYS 17
#define HEIGHT 400
#define WIDTH 1000
/*
#define LEFT 123
#define RIGHT 124
#define DOWN 125
#define UP 126
#define ZOOM 69
#define UNZOOM 78
#define QUIT 12
*/
const char		*g_message[NB_SPECIAL_KEYS + 1] = {
	"Appuie sur la fleche de gauche",
	"Appuie sur la fleche de droite",
	"Appuie sur la fleche du bas",
	"Appuie sur la fleche du haut",
	"Choisie le boutton ZOOM",
	"Choisie le boutton DEZOOM",
	"Choisie le boutton QUIT",
	"Choisie la rotation droite(X)",
	"Choisie la rotation gauche(X)",
	"Choisie la rotation droite(Y)",
	"Choisie la rotation gauche(Y)",
	"Choisie la rotation droite(Z)",
	"Choisie la rotation gauche(Z)",
	"Choisie le boutton afficher les information dans le terminal",
	"Choisie le boutton pour augmenter la profondeur",
	"Choisie le boutton pour reduire la profondeur",
	"Choisie le boutton passer a la prochaine projection",
	0x0
	};

const char		*g_define_name[NB_SPECIAL_KEYS + 1] = {"LEFT", "RIGHT", "DOWN",
				"UP", "ZOOM", "UNZOOM", "QUIT", "X_RIGHT",
				"X_LEFT", "Y_RIGHT", "Y_LEFT", "Z_RIGHT", "Z_LEFT", "INFOS",
				"DEEPER", "SHALLOWER", "NEXT_PROJECTION", 0x0};

t_specialkeys	*initialise_specialkeys(void)
{
	t_specialkeys	*res;

	res = (t_specialkeys *)malloc(sizeof(t_specialkeys));
	res->key_value = malloc(sizeof(int) * NB_SPECIAL_KEYS);
	res->mlx_ptr = mlx_init();
	res->size_x = WIDTH;
	res->size_y = HEIGHT;
	res->win_ptr = mlx_new_window(res->mlx_ptr,
			res->size_x, res->size_y, "get_keys");
	return (res);
}

int	get_keys(int key, void *param)
{
	static int		compteur = 0;
	int				i;
	t_specialkeys	*data;

	data = param;
	if (compteur >= 0)
		data->key_value[compteur] = key;
	if (compteur < NB_SPECIAL_KEYS)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 200, set_b(0, 255),
			(char*)g_message[compteur]);
	}
	else
	{
		i = 0;
		while (++i <= NB_SPECIAL_KEYS)
			printf("# define %s %d\n", g_define_name[i - 1], data->key_value[i]);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->key_value);
		free(data);
		exit(0);
	}
	compteur++;
	return (1);
}

int	check_constante(void)
{
	int	i;

	i = -1;
	while (++i < NB_SPECIAL_KEYS && g_message[i] && g_define_name[i])
		;
	if (i < NB_SPECIAL_KEYS || g_message[i] || g_define_name[i])
	{
		printf("Erreur nombre de touches special (%d %d)\n",
			NB_SPECIAL_KEYS, i);
		return (0);
	}
	return (1);
}

int	main(void)
{
	t_specialkeys	*mlx;

	if (!check_constante())
		return (1);
	mlx = initialise_specialkeys();
	mlx_key_hook(mlx->win_ptr, get_keys, mlx);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, mlx->size_y / 2,
		set_b(0, 255), "Appuie sur n'importe quelle touches");
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
