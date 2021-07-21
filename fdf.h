/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:44:06 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/21 17:40:53 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef __FDF_H__
#define __FDF_H__

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/includes/libft.h"

#define LEFT 123
#define RIGHT 124
#define DOWN 125
#define UP 126
#define ZOOM 69
#define UNZOOM 78
#define QUIT 12
#define ESC 53


typedef struct		s_mlx
{
	void*			mlx_ptr;
	void*			win;
	int				size_x;
	int				size_y;
}					t_mlx;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef enum		e_projection
{
	D2,
	ISOMETRIC,
	PARALLELE,
	CONIQUE
}					t_projection;

typedef struct		s_fdf
{
	t_point			**original_map;
	t_point			**map;
	t_mlx			*mlx;
	int				y_max;
	int				x_max;
	int				zoom;
	int				x_origin;
	int				y_origin;
	t_projection	type_projection;
}					t_fdf;

typedef struct		s_map
{
	int				**points;
	int				**color;
	int				y_max;
	int				x_max;
	int				zoom;
}					t_map;


int			set_b(int trgb, int b);
int			set_g(int trgb, int g);
int			set_r(int trgb, int r);
int			set_t(int trgb, int t);

int			set_trgb(int t, int r, int g, int b);

t_fdf		*parsing_map(t_fdf *map, const char *file_name);
void		plot(int x, int y);
int			set_r(int trgb, int r);

int			keys_action(int key, void *param);
int			draw_bressman_line(t_fdf *fdf, int x0, int x1, int y0, int y1);

void		draw_origin(t_fdf *fdf);
void		link_point(t_fdf *fdf);
void		process_draw(t_fdf *fdf);
void		change_projection(t_fdf *fdf, t_projection projection);
void		dislplay_map_infos(t_fdf *map);

#endif /* __FDF_H__ */
