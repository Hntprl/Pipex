/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:27:58 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/16 02:16:59 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	ch;

	i = 0;
	ch = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
		{
			i ++;
		}
		if (s[i] != '\0')
		{
			ch ++;
			i ++;
		}
		while (s[i] != c && s[i] != '\0')
		{
			i ++;
		}
	}
	return (ch);
}

int	ft_wordlen(const char *s, char c, int start)
{
	int	i;
	int	j;

	i = 0;
	j = start;
	while (s[j] != c && s[j] != '\0')
	{
		i ++;
		j ++;
	}
	return (i);
}

char	*ft_wordset(const char *s, char c, int start)
{
	char	*p;
	int		j;
	int		i;
	int		len;

	j = start;
	i = 0;
	len = ft_wordlen(s, c, start);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
	{
		return (NULL);
	}
	while (s[j] != '\0' && s[j] != c)
	{
		p[i] = s[j];
		i ++;
		j ++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (!s)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	str = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i ++;
		if (s[i] != '\0')
			str[j++] = ft_wordset(s, c, i++);
		while (s[i] != c && s[i] != '\0')
			i ++;
	}
	str[j++] = NULL;
	return (str);
}