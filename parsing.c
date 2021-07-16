/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:01:23 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/16 18:58:28 by anyahyao         ###   ########.fr       */
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


void		dislplay_map_infos(t_map *map)
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
			printf("%3d", map->points[i][j]);
		}
		printf("\n");
	}

}

t_map		*parsing_map(t_map *map, const char *file_name)
{
	int		fd;
	char	*line;
	int		gnl_ret;

	fd = open(file_name, O_RDONLY);
	gnl_ret = get_next_line2(fd, &line);
	if (gnl_ret < 0)
		return 0x0;
	map->x_max = count_number_string(line);
	map->y_max = 1;
	map->points = (int **)malloc(sizeof(int*) * (BUFFER_MAP + 1));
	map->points[0] = convert_string_to_arrays(line, map->x_max);
	while (get_next_line2(fd, &line) > 0)
	{
		map->y_max ++;
		if (map->y_max % BUFFER_MAP == 0)
		{
			map->points = (int**)realloc(map->points, 
					(map->y_max + BUFFER_MAP + 1) * sizeof(int*));
		}
		map->points[map->y_max-1] = convert_string_to_arrays(line, map->x_max);
		free(line);
	}
	dislplay_map_infos(map);
	return map;
}



