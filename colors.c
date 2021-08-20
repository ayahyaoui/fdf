/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:03:28 by anyahyao          #+#    #+#             */
/*   Updated: 2021/07/13 21:43:20 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
#define WHITE 16777215

/*
 *
 * Do not forget to count the depth
 * */
int get_color_height(float height)
{
	if (height > 0)
		return set_b(0, 255);
	else
		return WHITE;
}



int	get_t(int trgb)
{
	return (trgb & (0xFF << 24)) >> 24;
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16)) >> 16;
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8)) >> 8;
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}


/**
 * set_* prend une couleur sous forme TRGB et la valeur de 
 * la couleur "*" (comprise entre 0 et 255) a ajouter
 *
 * renvoie la nouvelle couleur en enlevant l'ancienne couleur "*"
 * et ajoutant celle en paramettre
 **/

int set_t(int trgb, int t)
{
	t %= 256;
	return ((trgb & ~(0xFF << 24)) + (t << 24));
}

int set_r(int trgb, int r)
{
	r %= 256;
	return ((trgb & ~(0xFF << 16)) + (r << 16));
}

int set_g(int trgb, int g)
{
	g %= 256;
	return ((trgb & ~(0xFF << 8)) + (g << 8));
}

int set_b(int trgb, int b)
{
	b %= 256;
	return ((trgb & ~0xFF) + b);
}
int set_trgb(int t, int r, int g, int b)
{
	t %= 256;
	r %= 256;
	g %= 256;
	b %= 256;
	return ((t << 24) + (r << 16) + (g << 8) + b);
}
