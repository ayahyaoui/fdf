/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 11:31:44 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/25 11:31:46 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "fdf.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strsub(char const *s, unsigned int beg, size_t len)
{
	char			*str;
	unsigned int	i;

	str = NULL;
	if (!s)
		return (NULL);
	i = 0;
	str = (char *)malloc(len + 1);
	if (!(str))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[i] = s[i + beg];
		i++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		index;
	char	*ptr1;
	char	*ptr2;

	index = 0;
	ptr1 = (char *)(unsigned long)s1;
	ptr2 = (char *)(unsigned long)s2;
	str = (char *)malloc(ft_strlen(ptr1) + ft_strlen(ptr2) + 1);
	if (!(str))
		return (NULL);
	while (s1 && *s1)
	{
		str[index] = *s1;
		++index;
		++s1;
	}
	while (s2 && *s2)
	{
		str[index] = *s2;
		++index;
		++s2;
	}
	str[index] = 0;
	return (str);
}

void	ft_strdel(char **as)
{
	if (!as)
		return ;
	free(*as);
	*as = NULL;
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)(unsigned long)s;
	if (!s)
		return (NULL);
	if (!c)
		return (ptr + ft_strlen(ptr));
	while (*s)
	{
		if (*s == c)
			return (ptr);
		s++;
	}
	return (0);
}
