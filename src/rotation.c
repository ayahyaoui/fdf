/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:08:33 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/06 20:08:35 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
Rotate X
1       0       0
cos     -sin    0
sin     cos     0

Rotate Y
cos     0       sin
0       1       0
-sin    0       cos

Rotate Z
cos     -sin     0
sin     cos     0
0       0       1
	 = {
		{(cos(theta * (p.z + p.y)) + cos(theta * (p.z - p.y))) /2,
		(-sin(theta * (p.z + p.y)) + sin(theta * (p.z - p.y)))/2,
		sin(theta * p.z)},
		{(-cos(theta * (p.z + p.y + p.x)) - cos(theta * (p.z - p.y + p.x))
		+ cos(theta * (p.z + p.y - p.x)) + cos(theta * (p.z - p.y - p.x)) 
		+ 2 * sin(theta * (p.y + p.x)) + 2 * sin(theta * (p.y - p.x))) / 4,

		(2 * cos(theta * (p.y + p.x)) + 2 * cos(theta * (p.y - p.x)) 
		+ sin(theta * (p.z+ p.y + p.x)) - sin(theta * (p.z - p.y + p.x))
		- sin(theta * (p.z+ p.y - p.x)) + sin(theta * (p.z - p.y - p.x))) / 4,

		(- sin(theta * (p.z+ p.x)) + sin(theta * (p.z- p.x))) / 2},

		{(-2 * cos(theta * (p.y + p.x)) + 2 * cos(theta * (p.y - p.x))
		- sin(theta * (p.z + p.y + p.x)) - sin(theta * (p.z - p.y + p.x))
		- sin(theta * (p.z + p.y - p.x)) - sin(theta * (p.z - p.y - p.x))) / 4,
		(-cos(theta * (p.z + p.y + p.x)) + cos(theta * (p.z - p.y + p.x))
		- cos(theta * (p.z + p.y - p.x))	+ cos(theta * (p.z - p.y - p.x))
		+ 2 * sin(theta * (p.y + p.x)) - 2 * sin(theta * (p.y - p.x))) / 4,
		(cos(theta * (p.z+ p.x)) + cos(theta * (p.z - p.x))) / 2}};
*/
void	rotate_total_point(t_point *point, t_point p, double theta)
{
	double	m[3][3];

	m[0][0] = (cos(theta * (p.z + p.y)) + cos(theta * (p.z - p.y))) / 2;
	m[0][1] = (-sin(theta * (p.z + p.y)) + sin(theta * (p.z - p.y))) / 2;
	m[0][2] = sin(theta * p.z);
	m[1][0] = (-cos(theta * (p.z + p.y + p.x)) - cos(theta * (p.z - p.y + p.x))
			+ cos(theta * (p.z + p.y - p.x)) + cos(theta * (p.z - p.y - p.x))
			+ 2 * sin(theta * (p.y + p.x)) + 2 * sin(theta * (p.y - p.x))) / 4;
	m[1][1] = (2 * cos(theta * (p.y + p.x)) + 2 * cos(theta * (p.y - p.x))
			+ sin(theta * (p.z + p.y + p.x)) - sin(theta * (p.z - p.y + p.x))
			- sin(theta * (p.z + p.y - p.x))
			+ sin(theta * (p.z - p.y - p.x))) / 4;
	m[1][2] = (-sin(theta * (p.z + p.x)) + sin(theta * (p.z - p.x))) / 2;
	m[2][0] = (-2 * cos(theta * (p.y + p.x)) + 2 * cos(theta * (p.y - p.x))
			- sin(theta * (p.z + p.y + p.x)) - sin(theta * (p.z - p.y + p.x))
			- sin(theta * (p.z + p.y - p.x))
			- sin(theta * (p.z - p.y - p.x))) / 4;
	m[2][1] = (-cos(theta * (p.z + p.y + p.x)) + cos(theta * (p.z - p.y + p.x))
			- cos(theta * (p.z + p.y - p.x)) + cos(theta * (p.z - p.y - p.x))
			+ 2 * sin(theta * (p.y + p.x)) - 2 * sin(theta * (p.y - p.x))) / 4;
	m[2][2] = (cos(theta * (p.z + p.x)) + cos(theta * (p.z - p.x))) / 2;
	point = multiply_matrix_rotation(m, point);
}

void	rotate_point_x(t_point *point, double theta)
{
	double	m[3][3];

	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[1][0] = 0;
	m[1][1] = cos(theta);
	m[1][2] = -sin(theta);
	m[2][0] = 0;
	m[2][1] = sin(theta);
	m[2][2] = cos(theta);
	point = multiply_matrix_rotation(m, point);
}

void	rotate_point_y(t_point *point, double theta)
{
	double	m[3][3];

	m[0][0] = cos(theta);
	m[0][1] = 0;
	m[0][2] = sin(theta);
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[2][0] = -sin(theta);
	m[2][1] = 0;
	m[2][2] = cos(theta);
	point = multiply_matrix_rotation(m, point);
}

void	rotate_point_z(t_point *point, double theta)
{
	double	m[3][3];

	m[0][0] = cos(theta);
	m[0][1] = -sin(theta);
	m[0][2] = 0;
	m[1][0] = sin(theta);
	m[1][1] = cos(theta);
	m[1][2] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	point = multiply_matrix_rotation(m, point);
}

/*
double	matrix_rotateX[3][3] = {{1, 0, 0},
								{0, cos(theta), -sin(theta)},
								{0, sin(theta), cos(theta)}};
	double	matrix_rotateY[3][3] = {{cos(theta), 0, sin(theta)},
								{0, 1, 0},
								{-sin(theta), 0, cos(theta)}};
	double	matrix_rotateZ[3][3] = {{cos(theta), -sin(theta), 0},
								{sin(theta), cos(theta), 0},
								{0, 0, 1}};
	if (type_rotate == ROTATION_X)
		point = multiply_matrix_rotation(matrix_rotateX, point);
	else if (type_rotate == ROTATION_Y)
		point = multiply_matrix_rotation(matrix_rotateY, point);
	else if (type_rotate == ROTATION_Z)
		point = multiply_matrix_rotation(matrix_rotateZ, point);
	else
		printf("Rotattion %d inconnue\n", type_rotate);
*/
void	rotate_point(t_point *point, double theta, t_type_rotation type_rotate)
{
	if (type_rotate == ROTATION_X)
		rotate_point_x(point, theta);
	else if (type_rotate == ROTATION_Y)
		rotate_point_y(point, theta);
	else if (type_rotate == ROTATION_Z)
		rotate_point_z(point, theta);
	else
		printf("Rotattion %d inconnue\n", type_rotate);
}

t_point	create_point(int a, int b, int c)
{
	t_point	p;

	p.x = a;
	p.y = b;
	p.z = c;
	return (p);
}

void	copy_point(t_point *p1, t_point p2)
{
	p1->x = p2.x;
	p1->y = p2.y;
	p1->z = p2.z;
	p1->color = p2.color;
}

void	center_not_move(t_fdf *fdf, t_point old_pos, t_point pos)
{
	fdf->infos.x_origin -= old_pos.x - pos.x;
	fdf->infos.y_origin -= old_pos.y - pos.y;
}

t_point	copy_center_map(t_fdf *fdf, t_point **map)
{
	t_point	center;
	int		middle;

	middle = fdf->infos.y_max / 2;
	center.x = map[middle][(int)(map[middle][0].x / 2)].x;
	center.y = map[middle][(int)(map[middle][0].x / 2)].y;
	return (center);
}

/*	
fdf->infos.x_origin -= center.x - fdf->map[middle]
[(int)(fdf->map[middle][0].x / 2)].x;
fdf->infos.y_origin -= center.y - fdf->map[middle]
[(int)(fdf->map[middle][0].x / 2)].y;
*/
void	rotate_precision(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	*point;
	t_point	old_center;

	old_center = copy_center_map(fdf, fdf->map);
	i = 0;
	while (i < fdf->infos.y_max)
	{
		j = 1;
		while (j < fdf->map[i][0].x)
		{
			copy_point(&(fdf->map[i][j]), fdf->original_map[i][j]);
			fdf->map[i][j].z += fdf->original_map[i][j].z * fdf->infos.deep;
			point = &(fdf->map[i][j]);
			rotate_total_point(point, create_point(fdf->angle.x,
					fdf->angle.z, fdf->angle.y), M_PI / 120);
			j++;
		}
		i++;
	}
	if (fdf->type_projection == ISOMETRIC)
		transform_isometric_map(fdf);
	center_not_move(fdf, old_center, copy_center_map(fdf, fdf->map));
	process_draw(fdf);
}

// TODOOOOOOOOO
void	rotate_direction(t_fdf *fdf, t_type_rotation direction, int sens)
{
	int		i;
	int		j;
	t_point	center;
	int		middle;

	middle = fdf->infos.y_max / 2;
	center.x = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x;
	center.y = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y;
	i = 0;
	while (i < fdf->infos.y_max)
	{
		j = 0;
		while (++j < fdf->map[i][0].x)
			rotate_point(&fdf->map[i][j], (M_PI * fdf->angle.pas / 120 * sens),
				direction);
		i++;
	}
	fdf->infos.x_origin -= center.x - fdf->map[middle]
	[(int)(fdf->map[middle][0].x / 2)].x;
	fdf->infos.y_origin -= center.y - fdf->map[middle]
	[(int)(fdf->map[middle][0].x / 2)].y;
	process_draw(fdf);
}
