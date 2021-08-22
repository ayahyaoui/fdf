/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 20:09:45 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/22 20:09:47 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = (void *)malloc(sizeof(char) * size);
	if (!(mem))
		return (0x0);
	while (size--)
		((unsigned char *)mem)[size] = 0;
	return (mem);
}

int	ft_isdigit(int b)
{
	if ((b > 47 && b < 58))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
        int i;
        int neg;
        int res;

        i = 0;
        neg = 1;
        res = 0;
        while (str[i] > 0 && str[i] < 33 && str[i] != 27)
                i++;
        if (str[i] == '+' || str[i] == '-')
        {
                if (str[i] == '-')
                        neg = -1;
                i++;
        }
        while (str[i] > 47 && str[i] < 58)
        {
                res = res * 10 + (int)str[i] - 48;
                i++;
        }
        return (neg * res);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
        while (n--)
                ((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
        return ((void *)dest);
}
void	*ft_realloc(void *l, int t)
{
        char    *s;

        if (!(s = (char *)malloc(sizeof(char) * t)))
                return (0x0);
        s = ft_memcpy(s, l, sizeof(char) * t);
		
        free(l);
        return (s);
}