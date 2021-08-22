/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 20:53:25 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/22 20:53:27 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

size_t	ft_strlen(const char *str)
{
	int i;

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
	if (!(str = (char *)malloc(len + 1)))
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
	if (!(str = (char *)malloc(ft_strlen(ptr1) + ft_strlen(ptr2) + 1)))
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
	char *ptr;

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
	char *str;

	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
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
	if (!(dup = (char *)malloc((ft_strlen(ptr) + 1) * sizeof(char))))
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
