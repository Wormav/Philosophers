/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:04:21 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/08 16:01:01 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size < 1)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

static int	ft_strlcat(char *dest, char *src, int size)
{
	int	dest_len;
	int	src_len;
	int	i;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (src_len + size);
	while (src[i] && dest_len + i < size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len_s1;
	int		len_s2;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len_s1 + 1);
	ft_strlcat(result, s2, len_s1 + len_s2 + 1);
	return (result);
}

char	*ft_strdup(char *src)
{
	char	*result;
	int		len;

	len = ft_strlen(src) + 1;
	result = malloc(sizeof(char) * len);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, src, len);
	return (result);
}

void	print_error(char *str)
{
	char	*red_color;
	char	*reset_color;

	red_color = "\033[1;31m";
	reset_color = "\033[0m";
	write(2, red_color, ft_strlen(red_color));
	write(2, str, ft_strlen(str));
	write(2, reset_color, ft_strlen(reset_color));
	write(2, "\n", 1);
}
