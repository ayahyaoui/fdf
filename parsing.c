/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:01:23 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/25 21:35:26 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include "libft/includes/libft.h"
#define BUFFER_MAP  128
#define DIMESION 3

int	count_number_string(char *line)
{
	int		i;
	int		number;
	int		was_number;

	i = -1;
	number = 0;
	was_number = 0;
	while (line[++i])
	{
		if (line[i] >= '0' && line[i] <= '9' && !was_number)
		{
			was_number = 1;
			number ++;
		}
		else
			was_number = 0;
	}
	return (number);
}

/**
 * converti une liste de nombre formqt string avec
 * un tableau d'entier
 *
 */
t_point	*convert_string_to_points(t_fdf *fdf, char *s, int y)
{
	t_point		*tab;
	int			i;
	int			number;
	int			size;


	size = count_number_string(s) + 1;
	if (size > fdf->x_max)
		fdf->x_max = size;
	tab = (t_point *)malloc(sizeof(t_point) * (size + 1));
	
	number = 1;
	i = 0;
	tab[0].z = size;
	tab[0].x = size;
	while (s[i] && number < size + 1)
	{
		tab[number].z = atoi(&s[i]);
		while (s[i] && !ft_isdigit(s[i]))
			i++;
		while (s[i] && ft_isdigit(s[i]))
			i++;
		number++;
	}
	return (tab);
}

void	dislplay_map_infos(t_fdf *map)
{
	int		i;
	int		j;

	if (map == 0x0)
	{
		printf("Error: dislplay_map_infos\n");
		return ;
	}
	printf("dimesion <%d, %d>\n", map->x_max, map->y_max);
	i = -1;
	while (++i < map->y_max)
	{
		for (j = 1; j < map->map[i][0].x; j++)
		{
			if (DIMESION > 2)
				printf("<%3d,%3d,%3d> ", map->map[i][j].x,
					map->map[i][j].y, map->map[i][j].z);
			else
				printf("<%3d,%3d> ", map->map[i][j].x,
					map->map[i][j].y);
		}
		printf("\n");
	}
}

/**
** change original_map
** change les malloc par memalloc 
*/
t_point	**create_3d_map(t_fdf *fdf)
{
	t_point		**map;
	int			i;
	int			j;
	int			ratio_y;
	int			ratio_x;

	printf("en creation\n");
	ratio_y = fdf->mlx->size_y / fdf->y_max;
	ratio_x = fdf->mlx->size_x / fdf->x_max;
	ratio_x /= 2;
	ratio_y /= 2;
	// Test
	ratio_x = 43;
	ratio_y = 43;

	map = (t_point **)malloc(sizeof(t_point *) * (fdf->y_max + 1));
	i = 0;
	printf("en creation\n");
	while (i < fdf->y_max)
	{
		map[i] = (t_point *)malloc(sizeof(t_point) * (fdf->x_max + 1));
		j = 1;
		map[i][0].x = fdf->original_map[i][0].x;
		while (j < fdf->original_map[i][0].x)
		{
			map[i][j].x = fdf->mlx->size_x / 4 + j * ratio_x;
			map[i][j].y = fdf->mlx->size_y / 4 + i * ratio_y;
			map[i][j].z = fdf->original_map[i][j].z * 8;
			map[i][j].color = 0;
			fdf->original_map[i][j].x = fdf->mlx->size_x / 4 + j * ratio_x;
			fdf->original_map[i][j].y = fdf->mlx->size_y / 4 + j * ratio_y;
			fdf->original_map[i][j].color = 0;
			j++;
		}
		i++;
	}
	printf("fin creation\n");
	return (map);
}

/*
 *	Suppose que le fichier contient une matrice de int
 *
 */
t_fdf	*parsing_map(t_fdf *fdf, const char *file_name)
{
	int		fd;
	char	*line;
	int		gnl_ret;

	fd = open(file_name, O_RDONLY);
	gnl_ret = get_next_line2(fd, &line);

	if (gnl_ret < 0)
		return (0x0);
	fdf->y_max = 1;
	fdf->original_map = (t_point **) malloc(sizeof(t_point *)
			* (BUFFER_MAP + 1));
	fdf->original_map[0] = convert_string_to_points(fdf, line,  0);
	while (get_next_line2(fd, &line) > 0)
	{
		fdf->y_max ++;
		if (fdf->y_max % BUFFER_MAP == 0)
		{
			fdf->original_map = (t_point **)realloc(fdf->original_map,
					(fdf->y_max + BUFFER_MAP + 1) * sizeof(t_point *));
		}
		fdf->original_map[fdf->y_max - 1] = convert_string_to_points(fdf, line,
				 fdf->y_max);
		free(line);
	}
	printf("Je vais creer une map\n");
	fdf->map = create_3d_map(fdf);
	fdf->zoom = 50;
	printf("Je vais creer une map\n");
	//dislplay_map_infos(fdf);
	return (fdf);
}
