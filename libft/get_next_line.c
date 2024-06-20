/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 07:42:52 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/05 08:48:00 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		setup(char **str, size_t *starti, char **line, int fd);
char	*check_create_buffer(char *str, size_t *starti, int fd);
char	*update_line_and_buffer(char *line, char *str, size_t starti, int fd);
char	*ft_strsjoin(char *s1, char *s2, size_t size);

char	*get_next_line(int fd)
{
	static size_t	starti;
	static char		*str;
	char			*line;
	int				i;

	if (!setup(&str, &starti, &line, fd))
		return (str = NULL, NULL);
	i = starti;
	while (str[i++] != '\n')
	{
		if (i >= BUFFER_SIZE)
		{
			line = update_line_and_buffer(line, str, starti, fd);
			if (line == NULL)
				return (str = NULL, NULL);
			starti = 0;
			i = 0;
		}
	}
	line = ft_strsjoin(line, str + starti, i - starti);
	if (line == NULL)
		return (free(str), str = NULL, NULL);
	return (starti = i, line);
}

char	*update_line_and_buffer(char *line, char *str, size_t starti, int fd)
{
	line = ft_strsjoin(line, str + starti, BUFFER_SIZE - starti);
	if (line == NULL)
		return (free(str), NULL);
	ft_bzero(str, BUFFER_SIZE + 1);
	if (read(fd, str, BUFFER_SIZE) < 1)
		return (free(line), free(str), NULL);
	return (line);
}

int	setup(char **str, size_t *starti, char **line, int fd)
{
	*str = check_create_buffer(*str, starti, fd);
	if (*str == NULL)
		return (0);
	*line = (char *)malloc(sizeof(char));
	if (*line == NULL)
		return (free(*str), 0);
	(*line)[0] = 0;
	return (1);
}

char	*check_create_buffer(char *str, size_t *starti, int fd)
{
	if (str != NULL)
		return (str);
	*starti = 0;
	str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, BUFFER_SIZE + 1);
	if (read(fd, str, BUFFER_SIZE) < 1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*ft_strsjoin(char *s1, char *s2, size_t size)
{
	char	*final_str;
	size_t	i;
	size_t	j;

	final_str = (char *)malloc((ft_strlen(s1) + size + 1) * sizeof(char));
	if (final_str == NULL)
		return (free(s1), NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		final_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size)
	{
		final_str[i] = s2[j];
		i++;
		j++;
	}
	final_str[i] = '\0';
	free(s1);
	return (final_str);
}
