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

#ifndef FDF_H

# define FDF_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
//# include "../libft/includes/libft.h"
# include "constante.h"
# include <math.h>

typedef struct s_img
{
	char			*draw_map;
	void			*img_ptr;
	int				width;
	int				height;
	int				size_line;
}					t_img;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;

	t_img			*main_img;
	t_img			*menu_img;
}					t_mlx;

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_point;

typedef struct s_rotation
{
	int				x;
	int				y;
	int				z;
	int				pas;
	int				nb_rotate;
}					t_rotation;

typedef enum e_projection
{
	PARALLELE,
	ISOMETRIC,
	D2,
	ORTHO,
	CONIQUE
}					t_projection;

/*
 *
 * // CHANGER zoom_x AVEC DES DEFINE
 */
typedef struct s_infos
{
	int				y_max;
	int				x_max;
	int				zoom;
	int				zoom_pas;
	int				zoom_x;
	int				zoom_y;
	int				deep;
	double			step_size;
	double			deep_pas;
	double			x_origin;
	double			y_origin;
}					t_infos;

typedef struct s_fdf
{
	t_point			**original_map;
	t_point			**map;
	t_mlx			*mlx;
	t_rotation		angle;
	t_infos			infos;
	t_projection	type_projection;
	int				*button_grad_y;
}					t_fdf;

typedef struct s_map
{
	int				**points;
	int				**color;
	int				y_max;
	int				x_max;
	int				zoom;
}					t_map;

int			get_color_height(float height);

int			set_b(int trgb, int b);
int			set_g(int trgb, int g);
int			set_r(int trgb, int r);
int			set_t(int trgb, int t);
int			set_trgb(int t, int r, int g, int b);

t_fdf		*parsing_map(t_fdf *map, const char *file_name);
void		plot(int x, int y);
int			set_r(int trgb, int r);
int			keys_action(int key, void *param);
void		draw_bressman_line(t_img *img, t_point p0, t_point p1, int diff_y);

void		draw_origin(t_fdf *fdf);
void		link_points(t_fdf *fdf);
void		process_draw(t_fdf *fdf);
void		change_projection(t_fdf *fdf, t_projection projection);
void		draw_menu(t_fdf *fdf);

void		dislplay_map_infos(t_fdf *map);
t_point		*multiply_matrix_rotation(double mat[3][3], t_point *point);

void		rotateX(t_fdf *fdf, int sens);
void		rotateY(t_fdf *fdf, int sens);
void		rotateZ(t_fdf *fdf, int sens);
void		rotate_direction(t_fdf *fdf, t_type_rotation direction, int sens);

void		rotate_precision(t_fdf *fdf);
double		get_proportion(t_fdf *fdf, t_option op);
t_point		get_pixel_center(t_fdf *fdf);

void		initialise_fdf(t_fdf *fdf, t_mlx *mlx, t_img *main, t_img *menu);
int			mouse_event(int button, int x, int y, void *param);

int			put_graduation(t_fdf *fdf, char t_minus[], char t_plus[], int y);
void		draw_menu_graduation(t_fdf *fdf, t_img *img, const t_menu *type,
				const t_option options[]);
void		draw_graduation(t_fdf *fdf, int pos_y, int lim_y, t_option option);

void		put_point_color(t_img *img, int x, int y, int color);
void		draw_main_img(t_fdf *fdf, t_img *img);
void		display_fdfinfos(t_fdf *fdf);
void		transform_isometric_map(t_fdf *fdf);
int			process_next_projection(t_fdf *fdf);
void		process_cleaning(t_fdf *fdf);

// utils_rotate

//void		put_point_menu_color(t_mlx *mlx, int x, int y, int color);
t_point		create_point(int a, int b, int c);
void		copy_point(t_point *p1, t_point p2);
void		center_not_move(t_fdf *fdf, t_point old_pos, t_point pos);
t_point		copy_center_map(t_fdf *fdf, t_point **map);
void		rotate_direction(t_fdf *fdf, t_type_rotation direction, int sens);
void		rotate_total_point(t_point *point, t_point p, double theta);
void	rotate_point(t_point *point, double theta, t_type_rotation type_rotate);


void	*ft_realloc(void *l, int t);
int		ft_atoi(char *str);
void	ft_bzero(void *s, size_t n);
char	*ft_strdupf(char *dest, const char *src, int to_free);
void	*ft_memset(void *str, int c, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_strdel(char **as);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnew(size_t size);
char	*ft_strsub(char const *s, unsigned int beg, size_t len);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int b);
void	*ft_memalloc(size_t size);
int		get_next_line2(const int fd, char **line);


#endif
