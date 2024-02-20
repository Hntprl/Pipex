/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:57:39 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/20 00:57:42 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		c1 = s1[i];
		c2 = s2[i];
		if (c1 != c2)
		{
			return (c1 - c2);
		}
		i++;
	}
	return (0);
}

void ft_here_dock(int argc, char **argv, int fd[2])
{
    char *str;

    str = NULL;
    if (argc < 6)
        (close_fd(fd), exit(EXIT_FAILURE));
    if (fork() == 0)
    {
       while (1)
        {
            str = get_next_line(0);
            if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0)
                (free(str), close_fd(fd));
            exit(1);
        } 
        write(fd[1], str, ft_strlen(str));
        free(str);
    }   
}