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

/*
*	TODO deplacer la fonction autre par
*	count_number_string 
*		renvois: le nombre de nombre dans la string
**/
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
	if (size > fdf->infos.x_max)
		fdf->infos.x_max = size;
	tab = (t_point *)ft_memmalloc(sizeof(t_point) * (size + 1));
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

/**
** change original_map
** change les malloc par memalloc 
*/
t_point	**create_3d_map(t_fdf *fdf, t_img *img)
{
	t_point		**map;
	int			i;
	int			j;

	map = (t_point **)ft_memmalloc(sizeof(t_point *) * (fdf->infos.y_max + 1));
	i = 0;
	while (i < fdf->infos.y_max)
	{
		map[i] = ft_memmalloc(sizeof(t_point) * (fdf->infos.x_max + 1));
		j = 0;
		map[i][0].x = fdf->original_map[i][0].x;
		while (++j < fdf->original_map[i][0].x)
		{
			map[i][j].x = j * 10;
			map[i][j].y = i * 10;
			map[i][j].z = fdf->original_map[i][j].z;
			fdf->original_map[i][j].x = j * 10;
			fdf->original_map[i][j].y = i * 10;
		}
		i++;
	}
	fdf->infos.x_origin = 0;
	fdf->infos.y_origin = 0;
	printf("main img created\n");
	return (map);
}

/*
 *	Suppose que le fichier contient une matrice de int
 * ..
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
	fdf->infos.y_max = 1;
	fdf->original_map = (t_point **) ft_memmalloc(sizeof(t_point *)
			* (BUFFER_MAP + 1));
	fdf->original_map[0] = convert_string_to_points(fdf, line, 0);
	while (get_next_line2(fd, &line) > 0)
	{
		fdf->infos.y_max ++;
		if (fdf->infos.y_max % BUFFER_MAP == 0)
			fdf->original_map = (t_point **)realloc(fdf->original_map,
					(fdf->infos.y_max + BUFFER_MAP + 1) * sizeof(t_point *));
		fdf->original_map[fdf->infos.y_max - 1] = convert_string_to_points
			(fdf, line, fdf->infos.y_max);
		free(line);
	}
	fdf->map = create_3d_map(fdf, fdf->mlx->main_img);
	return (fdf);
}
