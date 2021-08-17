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
*/

void    rotate_total_point(t_point *point, int a, int b, int c, double theta)
{
    double matrix_rotation[3][3] = {{  (cos(theta * (c+b))+cos(theta * (c-b))) /2,                      (-sin(theta * (c+b))+sin(theta * (c-b)))/2, 	                                              sin(theta * c)},
        {(-cos(theta * (c+b+a))-cos(theta * (c-b+a))+cos(theta * (c+b-a))+cos(theta * (c-b-a))+2*sin(theta * (b+a))+2*sin(theta * (b-a)))/4,	 (2*cos(theta * (b+a))+2*cos(theta * (b-a))+sin(theta * (c+b+a))-sin(theta * (c-b+a))-sin(theta * (c+b-a))+sin(theta * (c-b-a)))/4,  (-sin(theta * (c+a))+sin(theta * (c-a)))/2}, 
        {(-2*cos(theta * (b+a))+2*cos(theta * (b-a))-sin(theta * (c+b+a))-sin(theta * (c-b+a))-sin(theta * (c+b-a))-sin(theta * (c-b-a)))/4,	(-cos(theta * (c+b+a))+cos(theta * (c-b+a))-cos(theta * (c+b-a))+cos(theta * (c-b-a))+2*sin(theta * (b+a))-2*sin(theta * (b-a)))/4,	 (cos(theta * (c+a))+cos(theta * (c-a)))/2}
    };

     point = multiply_matrix_rotation(matrix_rotation, point);
}
        





void    rotate_point(t_point    *point, double theta, t_type_rotation type_rotate)
{
    double matrix_rotateX[3][3] =  {{1, 0, 0}, 
                                {0, cos(theta), -sin(theta)}, 
                                {0, sin(theta), cos(theta)}};
    double matrix_rotateY[3][3] =  {{cos(theta), 0, sin(theta)}, 
                                {0, 1, 0}, 
                                {-sin(theta), 0, cos(theta)}};
    double matrix_rotateZ[3][3] =   {{cos(theta), -sin(theta), 0}, 
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
    
}

















void    rotate_precision(t_fdf *fdf)
{
    int     i;
    int     j;
    t_point *point;
    t_point center;
    int     middle;

    middle = fdf->infos.y_max / 2;
    center.x = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x;
    center.y = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y;
    i = 0;
    while (i < fdf->infos.y_max)
    {
        j = 1;
		while (j < fdf->map[i][0].x)
		{
            fdf->map[i][j].x = fdf->original_map[i][j].x;
            fdf->map[i][j].y = fdf->original_map[i][j].y;
            fdf->map[i][j].z = fdf->original_map[i][j].z + fdf->original_map[i][j].z * fdf->infos.deep;
		    point = &(fdf->map[i][j]);
            rotate_total_point(point, fdf->angle.x, fdf->angle.z, fdf->angle.y, M_PI / 120);
            j++;
		}
		i++;
    }
    fdf->infos.x_origin -= center.x - fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x;
    fdf->infos.y_origin -= center.y - fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y;
    process_draw(fdf);
}

// TODOOOOOOOOO
void    rotate_direction(t_fdf *fdf, t_type_rotation direction, int sens)
{
    int     i;
    int     j;
    t_point center;
    int     middle;

    //printf("rotation Totale %d, %d, %d\n", fdf->angle.x, fdf->angle.y, fdf->angle.z);
    //printf("rotation Totale %d, %d, %d\n", fdf->infos.x_max, fdf->infos.y_max,fdf->infos.zoom  );
    middle = fdf->infos.y_max / 2;
    center.x = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x;
    center.y = fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y;
    i = 0;
    while (i < fdf->infos.y_max)
    {
        j = 0;
		while (++j < fdf->map[i][0].x)
            rotate_point(&fdf->map[i][j], (M_PI * fdf->angle.pas / 120 * sens), direction);

		i++;
    }
    fdf->infos.x_origin -= center.x - fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].x;
    fdf->infos.y_origin -= center.y - fdf->map[middle][(int)(fdf->map[middle][0].x / 2)].y;
    process_draw(fdf);
}
