/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 11:31:16 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/25 11:31:18 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*string;

	string = (unsigned char *)str;
	while (len)
	{
		*(string) = (unsigned char)c;
		--len;
		string++;
	}
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc((size + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char	*ft_strdupf(char *dest, const char *src, int to_free)
{
	int		i;
	char	*dup;
	size_t	len;
	char	*ptr;

	dup = NULL;
	ptr = (char *)(unsigned long)src;
	dup = (char *)malloc((ft_strlen(ptr) + 1) * sizeof(char));
	if (!(dup))
		return (NULL);
	i = 0;
	len = ft_strlen(ptr);
	while (len--)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	if ((to_free == 2 || to_free == 3) && src != NULL)
		ft_strdel(&ptr);
	if ((to_free == 1 || to_free == 3) && dest != NULL)
		ft_strdel(&ptr);
	return (dup);
}

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
