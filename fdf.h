/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:44:06 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/16 22:29:48 by anyahyao         ###   ########.fr       */
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

/*
typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;
*/

typedef struct		s_map
{
	int				**points;
	int				**color;
	int				y_max;
	int				x_max;
	int				zoom;
}					t_map;


int set_b(int trgb, int b);
int set_g(int trgb, int g);
int set_r(int trgb, int r);
int set_t(int trgb, int t);

int set_trgb(int t, int r, int g, int b);


#endif /* __FDF_H__ */
