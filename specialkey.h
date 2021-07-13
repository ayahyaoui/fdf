/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialkey.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:47:57 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/13 21:43:19 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __SPECIALKEY_H__
#define __SPECIALKEY_H__

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_specialkeys
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				size_x;
	int				size_y;
	int				*key_value;
}					t_specialkeys;



int set_b(int trgb, int b);
int set_g(int trgb, int g);
int set_r(int trgb, int r);
int set_t(int trgb, int t);

int set_trgb(int t, int r, int g, int b);

#endif /* __SPECIALKEY_H__ */
