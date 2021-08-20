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

#define BUFFER_MAP  128
#define SPACE_X 2
#define SPACE_Y 2
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
	tab = (t_point *)ft_memalloc(sizeof(t_point) * (size + 1));
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

void	center_map(t_fdf *fdf)
{
	double	range_w;
	double	range_h;

	range_w = fdf->infos.x_max * SPACE_X * fdf->infos.zoom_x * fdf->infos.zoom;
	range_h = fdf->infos.y_max * SPACE_Y * fdf->infos.zoom_y * fdf->infos.zoom;
	if (range_w < fdf->mlx->main_img->width
		&& range_h < fdf->mlx->main_img->height)
	{
		fdf->infos.x_origin = -(fdf->mlx->main_img->width - range_w)
			/ (2 * fdf->infos.zoom_x * fdf->infos.zoom);
		fdf->infos.y_origin = -(fdf->mlx->main_img->height - range_h)
			/ (2 * fdf->infos.zoom_y * fdf->infos.zoom);
	}
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

	map = (t_point **)ft_memalloc(sizeof(t_point *) * (fdf->infos.y_max + 1));
	i = 0;
	while (i < fdf->infos.y_max)
	{
		map[i] = ft_memalloc(sizeof(t_point) * (fdf->infos.x_max + 1));
		j = 0;
		map[i][0].x = fdf->original_map[i][0].x;
		while (++j < fdf->original_map[i][0].x)
		{
			map[i][j].x = j * SPACE_X;
			map[i][j].y = i * SPACE_Y;
			map[i][j].z = fdf->original_map[i][j].z;
			fdf->original_map[i][j].x = j * SPACE_X;
			fdf->original_map[i][j].y = i * SPACE_Y;
		}
		i++;
	}
	center_map(fdf);
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
	fdf->original_map = (t_point **) ft_memalloc(sizeof(t_point *)
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
