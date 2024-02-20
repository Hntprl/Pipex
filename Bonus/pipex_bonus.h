/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:16:42 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/20 00:49:17 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

void	ft_free(char **str);
void ft_here_dock(int argc, char **argv, int fd[2]);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_findpath(char **envp);
char	*ft_checkaccess(char **envp, char *cmd);
void ft_first_command(char **argv, char **envp, int fd[2]);
void ft_all_commands(char *cmd, char **envp, int fd[2]);
void ft_last_command(char **argv, char **envp, int argc, int fd[2]);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
void	close_fd(int fd[2]);
char	**ft_split(char const *s, char c);

#endif