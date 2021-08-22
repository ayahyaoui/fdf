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
