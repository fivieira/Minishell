/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:45:46 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/19 16:22:38 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s == NULL)
		return (write(fd, "(null)", 6));
	len = ft_strlen(s);
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	return (len);
}
