/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:33:26 by afantes           #+#    #+#             */
/*   Updated: 2022/11/11 16:33:28 by afantes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read(int fd, char *stat)
{
	char	*buff;
	int		n;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	n = 1;
	while (ft_strchr(stat, '\n') == NULL && n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[n] = '\0';
		stat = ft_strjoin(stat, buff);
	}
	free(buff);
	return (stat);
}

/*------------------------------------------*/

static char	*get_line(char *stat)
{
	char	*line;
	size_t	l;
	size_t	i;

	l = 0;
	if (stat[0] == '\0')
		return (NULL);
	while (stat[l] != '\n' && stat[l] != '\0')
		l++;
	if (stat[l] == '\n')
		l++;
	line = (char *)malloc((l + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < l)
	{
		line[i] = stat[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*------------------------------------------*/

static char	*ft_save(char *stat)
{
	char	*new;
	size_t	l;
	size_t	i;

	l = 0;
	while (stat[l] != '\n' && stat[l] != '\0')
		l++;
	if (ft_strlen(stat) == l)
	{
		free(stat);
		return (NULL);
	}
	new = (char *)malloc((ft_strlen(stat) - l + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (stat[l++] != '\0')
	{
		new[i] = stat[l];
		i++;
	}
	new[i] = '\0';
	free(stat);
	return (new);
}

/*------------------------------------------*/

char	*get_next_line(int fd)
{
	static char	*stat[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat[fd] = ft_read(fd, stat[fd]);
	if (stat[fd] == NULL)
		return (NULL);
	line = get_line(stat[fd]);
	stat[fd] = ft_save(stat[fd]);
	return (line);
}
