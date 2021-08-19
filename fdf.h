/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:44:06 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/25 21:38:35 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef __FDF_H__
#define __FDF_H__

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/includes/libft.h"
#include "constante.h"


typedef struct 		s_img
{
	char*			draw_map;
	void*			img_ptr; //img_map
	int				width;
	int				height;
	int				size_line;
}					t_img;


typedef struct		s_mlx
{
	void*			mlx_ptr;
	void*			win;

	t_img*			main_img;
	t_img*			menu_img;
	/*
	void*			img_map;
	char*			draw_map;
	int				size_line;
	int				size_x; // width
	int				size_y; // height

	void*			img_menu;
	char*			draw_menu;
	int				size_line_menu;
	int 			width_menu;
	*/
}					t_mlx;

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_point;

typedef struct 		s_rotation
{
	int				x;
	int				y;
	int				z;
	int				pas; // pas * 10 pi / 120
	int				nb_rotate;
}					t_rotation;

typedef enum		e_projection
{
	D2,
	ORTHO,
	ISOMETRIC,
	PARALLELE,
	CONIQUE
}					t_projection;


typedef struct 		s_infos
{
	int				y_max;
	int				x_max;
	int				zoom;
	int 			zoom_pas;
	int 			zoom_x; // CHANGER AVEC DES DEFINE
	int				zoom_y; // CHANGER AVEC DES DEFINE
	int				deep;
	double			step_size;
	double			deep_pas;
	double			x_origin;
	double			y_origin;
}					t_infos;

typedef struct		s_fdf
{
	t_point			**original_map;
	t_point			**map;
	t_mlx			*mlx;
	t_rotation		angle;
	t_infos			infos;
	t_projection	type_projection;
	int				*button_grad_y;
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
void			draw_bressman_line(t_img *img, t_point p0, t_point p1);

void		draw_origin(t_fdf *fdf);
void		link_points(t_fdf *fdf);
void		process_draw(t_fdf *fdf);
void		change_projection(t_fdf *fdf, t_projection projection);
void        draw_menu(t_fdf *fdf);

void		dislplay_map_infos(t_fdf *map);
t_point     *multiply_matrix_rotation(double mat[3][3], t_point *point);


void    	rotateX(t_fdf   *fdf, int sens);
void    	rotateY(t_fdf   *fdf, int sens);
void    	rotateZ(t_fdf   *fdf, int sens);
void    	rotate_direction(t_fdf *fdf, t_type_rotation direction, int sens);

void    	rotate_precision(t_fdf *fdf);
double      get_proportion(t_fdf *fdf, t_option op);
t_point     get_pixel_center(t_fdf *fdf);


void		initialise_fdf(t_fdf *fdf, t_mlx *mlx, t_img *main, t_img *menu);
int 		mouse_event(int button, int x, int y, void *param);


int         put_graduation(t_fdf *fdf, char title_minus[], char title_plus[], int y);
void		draw_menu_graduation(t_fdf *fdf, t_img *img, const t_menu *type, const t_option options[]);
void		draw_graduation(t_fdf *fdf, int pos_y, int lim_y, t_option option);

void		put_point_color(t_img *img, int x, int y, int color);
void	draw_main_img(t_fdf *fdf, t_img *img);
void	display_fdfinfos(t_fdf *fdf);

//void		put_point_menu_color(t_mlx *mlx, int x, int y, int color);

#endif /* __FDF_H__ */
