/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:16:42 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/16 02:53:38 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void ft_free(char **str);
void close_fd(int fd[2]);
char	*ft_strdup(const char *s1);
void ft_command1(char **argv, char **envp, int fd[2]);
void ft_command2(char **argv, char **envp, int fd[2]);
char *ft_checkaccess(char **envp, char *cmd);
char *ft_findpath(char **envp);
char	**ft_split(char const *s, char c);
int	ft_wordcount(const char *s, char c);
int	ft_wordlen(const char *s, char c, int start);
char	*ft_wordset(const char *s, char c, int start);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
#endif