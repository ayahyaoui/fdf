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


t_point     *multiply_matrix_rotation(float mat[3][3], t_point *point)
{
    int     old_point[3];
    float   result[3];
    int     i;
    int     j;

    //printf("before %d %d %d\n", point->x, point->y, point->z);
    i = -1;
    old_point[0] = point->x;
    old_point[1] = point->y;
    old_point[2] = point->z;
    while (++i < 3)
        result[i] = 0.0;
    i = -1;
    while (++i < 3)
    {
        j = -1;
        while (++j < 3)
            result[i] += mat[i][j] * old_point[j];

    }
    point->x = result[0];
    point->y = result[1];
    point->z = result[2];
    
    
    //printf("result %d %d %d\n", point->x, point->y, point->z);
    return point;
}





void    rotate_pointX(t_point   *point, float theta)
{
    float mat_rotate[3][3] =   {{1, 0, 0}, 
                                {0, cos(theta), -sin(theta)}, 
                                {0, sin(theta), cos(theta)}};
    
    point = multiply_matrix_rotation(mat_rotate, point);
    
}

/*
Titate X
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
*/

void    rotate_pointY(t_point   *point, float theta)
{
    //printf("angle %f\n", theta);
    float mat_rotate[3][3] =   {{cos(theta), 0, sin(theta)}, 
                                {0, 1, 0}, 
                                {-sin(theta), 0, cos(theta)}};
    
   
    point = multiply_matrix_rotation(mat_rotate, point);
}


void    rotate_pointZ(t_point   *point, float theta)
{
    float mat_rotate[3][3] =   {{cos(theta), -sin(theta), 0}, 
                                {sin(theta), cos(theta), 0}, 
                                {0, 0, 1}};
    
    point = multiply_matrix_rotation(mat_rotate, point);
}

void   rotateX(t_fdf *fdf, int direction)
{
    int     i;
    int     j;
    t_point *point;
    t_point center;
    int     middle;

    printf("rotation X\n");
    //dislplay_map_infos(fdf);
    
    middle = fdf->y_max / 2;
    center.x = fdf->map[middle][fdf->map[middle][0].x / 2].x;
    center.y = fdf->map[middle][fdf->map[middle][0].x / 2].y;
    i = 0;
    while (i < fdf->y_max)
    {
        j = 1;
		while (j < fdf->map[i][0].x)
		{
			point = &(fdf->map[i][j]);
			rotate_pointX(point, (M_PI / 12) * direction);
			j++;
		}
		i++;
    }
    fdf->x_origin -= center.x - fdf->map[middle][fdf->map[middle][0].x / 2].x;
    fdf->y_origin -= center.y - fdf->map[middle][fdf->map[middle][0].x / 2].y;
    process_draw(fdf);
}

void   rotateY(t_fdf *fdf, int direction)
{
    int     i;
    int     j;
    t_point *point;
    t_point center;
    int     middle;

    printf("rotation Y\n");
    //dislplay_map_infos(fdf);
    
    middle = fdf->y_max / 2;
    center.x = fdf->map[middle][fdf->map[middle][0].x / 2].x;
    center.y = fdf->map[middle][fdf->map[middle][0].x / 2].y;
    i = 0;
    while (i < fdf->y_max)
    {
        j = 1;
		while (j < fdf->map[i][0].x)
		{
			point = &(fdf->map[i][j]);
			rotate_pointY(point, (M_PI / 12) * direction);
			j++;
		}
		i++;
    }
    fdf->x_origin -= center.x - fdf->map[middle][fdf->map[middle][0].x / 2].x;
    fdf->y_origin -= center.y - fdf->map[middle][fdf->map[middle][0].x / 2].y;
    process_draw(fdf);
}

void   rotateZ(t_fdf *fdf, int direction)
{
    int     i;
    int     j;
    t_point *point;
    t_point center;
    int     middle;

    printf("rotation Z\n");
    //dislplay_map_infos(fdf);
    
    middle = fdf->y_max / 2;
    center.x = fdf->map[middle][fdf->map[middle][0].x / 2].x;
    center.y = fdf->map[middle][fdf->map[middle][0].x / 2].y;
    i = 0;
    while (i < fdf->y_max)
    {
        j = 1;
		while (j < fdf->map[i][0].x)
		{
			point = &(fdf->map[i][j]);
			rotate_pointZ(point, (M_PI / 12) * direction);
			j++;
		}
		i++;
    }

    fdf->x_origin -= center.x - fdf->map[middle][fdf->map[middle][0].x / 2].x;
    fdf->y_origin -= center.y - fdf->map[middle][fdf->map[middle][0].x / 2].y;
    process_draw(fdf);
}
