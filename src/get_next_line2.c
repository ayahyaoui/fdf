/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 20:15:40 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/22 20:15:46 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define SEP '\n'
#define BUFF_SIZE 200

void	ft_bzero(void *s, size_t n);
char	*ft_strdupf(char *dest, const char *src, int to_free);
void	*ft_memset(void *str, int c, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_strdel(char **as);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnew(size_t size);
char	*ft_strsub(char const *s, unsigned int beg, size_t len);
size_t	ft_strlen(const char *str);

static char	*ft_strjoinfree(char *str, char *str2)
{
	char	*new;

	new = NULL;
	if (!str)
		return (ft_strdupf(new, str2, 0));
	new = ft_strjoin(str, str2);
	if (!(new))
		ft_strdel(&str2);
	ft_memset((void *)str2, 0, (size_t)BUFF_SIZE + 1);
	ft_strdel(&str);
	return (new);
}

size_t	get_j(size_t i, char *str)
{
	size_t	j;

	if (str[i])
		j = i + 1;
	else
	{
		j = i;
		i--;
	}
	while (str[j] != 0)
		j++;
	return (j);
}

static char	*ft_split_buff(char *str, int option)
{
	size_t		i;
	size_t		j;
	char		*line;

	i = 0;
	line = NULL;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (option == 1)
	{
		line = ft_strsub(str, 0, i);
		if (!(line))
			ft_strdel(&str);
	}
	else if (option == 2)
	{
		j = get_j(i, str);
		if (!str[i])
			i--;
		line = ft_strsub(str, (unsigned int)(i + 1), j - i - 1);
		ft_strdel(&str);
	}
	return (line);
}

static int	inner_gnl(int fd, long int *ret, char **remain, char **buffer)
{
	while (!ft_strchr(*remain, SEP))
	{
		*ret = read(fd, *buffer, BUFF_SIZE);
		if (*ret <= 0)
			break ;
		if (*ret == BUFF_SIZE)
		{
			*remain = ft_strjoinfree(*remain, *buffer);
			if (!*remain)
			{
				ft_strdel(buffer);
				return (-1);
			}
		}
		if (*ret < BUFF_SIZE)
			*remain = ft_strjoinfree(*remain, *buffer);
		ft_bzero(*buffer, BUFF_SIZE);
	}
	ft_strdel(buffer);
	if (*ret == 0 && *remain && (*remain)[0] == 0)
	{
		ft_strdel(remain);
		return (0);
	}
	return (1);
}

int	get_next_line2(const int fd, char **line)
{
	static char		*remain;
	char			*buffer;
	long int		ret;

	buffer = NULL;
	ret = read(fd, "", 0);
	if (BUFF_SIZE <= 0 || ret == -1 || fd < 0)
		return (-1);
	buffer = ft_strnew(BUFF_SIZE + 1);
	if (!(buffer))
		return (-1);
	if (!inner_gnl(fd, &ret, &remain, &buffer))
		return (0);
	if (remain)
	{
		*line = ft_split_buff(remain, 1);
		if (!*line)
		{
			ft_strdel(&remain);
			return (-1);
		}
	}
	remain = ft_split_buff(remain, 2);
	return (1);
}
