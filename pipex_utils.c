/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:16:54 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/16 00:25:23 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i ++]);
	free(str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i ++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *) malloc(ft_strlen(s1) + 1 * sizeof(char));
	if (p == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i ++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j ++;
			}
			j = 0;
		}
		i ++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (p == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i ++;
	}
	while (s2[j] != '\0')
	{
		p[i + j] = s2[j];
		j ++;
	}
	p[i + j] = '\0';
	return (p);
}
