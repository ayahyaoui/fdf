/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:01:23 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/20 21:04:30 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include "libft/includes/libft.h"
#define BUFFER_MAP  128

/**
 *	compte le nombre de nombre dans une string
 *
 */
int		count_number_string(char *line)
{
	int i;
	int number;
	int was_number;

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
	return number;
}

/**
 * converti une liste de nombre formqt string avec
 * un tableau d'entier
 *
 */
int		*convert_string_to_arrays(char *s, int size)
{
	int		*tab;
	int		i;
	int		number;

	if (count_number_string(s) != size)
	{
		printf("Error: nombre d element mauvais %d\n", size);
		return 0x0;
	}
	tab = (int *)malloc(sizeof(int) * size);

	number = 0;
	i = 0;
	while (s[i] && number < size)
	{
		tab[number] = atoi(&s[i]);
		while (s[i] && !ft_isdigit(s[i]))
			i++;
		while (s[i] && ft_isdigit(s[i]))
			i++;
		number++;
	}
	return tab;
}


void		dislplay_map_infos(t_fdf *map)
{
	int i;
	int j;

	if (map == 0x0)
	{
		printf("Error: dislplay_map_infos\n");
	return;
	}
	printf("dimesion <%d, %d>\n", map->x_max, map->y_max);
	i = -1;
	while (++i < map->y_max)
	{
		j = 0;
		for (j = 0; j < map->x_max ; j++)
		{
			printf("%3d", map->original_map[i][j]);
		}
		printf("\n");
	}

}

// change les malloc par memalloc 
t_point		**create_3d_map(t_fdf *fdf)
{
	t_point		**map;
	int i;
	int j;
	int ratio_y;
	int ratio_x;

	ratio_y = fdf->mlx->size_y / fdf->y_max;
	ratio_x = fdf->mlx->size_x / fdf->x_max;
	ratio_x /=2;
	ratio_y /=2;
	map = (t_point **)malloc(sizeof(t_point*) * (fdf->y_max + 1));
	i = 0;
	while (i < fdf->y_max)
	{
		map[i] = (t_point *)malloc(sizeof(t_point) * (fdf->x_max + 1));
		j = 0;
		while (j < fdf->x_max)
		{
			map[i][j].x =fdf->mlx->size_x / 4 + j * ratio_x;
			map[i][j].y = fdf->mlx->size_y / 4 + i * ratio_y;
			map[i][j].z = fdf->original_map[i][j];
			map[i][j].color = 0;
			j++;
		}
		i++;
	}
	return (map);
}

/*
 *	Suppose que le fichier contient une matrice de int
 *
 */
t_fdf		*parsing_map(t_fdf *fdf, const char *file_name)
{
	int		fd;
	char	*line;
	int		gnl_ret;

	fd = open(file_name, O_RDONLY);
	gnl_ret = get_next_line2(fd, &line);
	if (gnl_ret < 0)
		return 0x0;
	fdf->x_max = count_number_string(line);
	fdf->y_max = 1;
	fdf->original_map = (int **)malloc(sizeof(int*) * (BUFFER_MAP + 1));
	fdf->original_map[0] = convert_string_to_arrays(line, fdf->x_max);
	while (get_next_line2(fd, &line) > 0)
	{
		fdf->y_max ++;
		if (fdf->y_max % BUFFER_MAP == 0)
		{
			fdf->original_map = (int**)realloc(fdf->original_map, 
					(fdf->y_max + BUFFER_MAP + 1) * sizeof(int*));
		}
		fdf->original_map[fdf->y_max-1] = convert_string_to_arrays(line, fdf->x_max);
		free(line);
	}
	fdf->map = create_3d_map(fdf);
	dislplay_map_infos(fdf);
	return fdf;
}



