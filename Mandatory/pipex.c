/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:16:27 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/24 22:10:14 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_findpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 4) != NULL)
			return ((envp[i] + 5));
		i ++;
	}
	return (NULL);
}

char	*ft_checkaccess(char **envp, char *cmd)
{
	int		i;
	char	**allpaths;
	char	*path;
	char	*leakpath;

	i = 0;
	allpaths = ft_split(ft_findpath(envp), ':');
	if (allpaths == NULL)
		exit(EXIT_FAILURE);
	while (allpaths[i] != NULL)
	{
		leakpath = ft_strjoin(allpaths[i], cmd);
		if (access(leakpath, F_OK) == 0)
		{
			free(leakpath);
			path = ft_strdup(allpaths[i]);
			return (free_strings(allpaths), path);
		}
		free(leakpath);
		i ++;
	}
	free_strings(allpaths);
	exit(write(2, "Command not found !\n", 20));
	return (NULL);
}

void	ft_command2(char **argv, char **envp, int fd[2])
{
	char	**cmd;
	char	*cmd2;
	int		fl2;

	if (!argv[2][0] || !argv[3][0])
		exit(write(2, "Enter a command!\n", 17));
	fl2 = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fl2 == -1)
		exit(write(2, "can't open the output file!\n", 27));
	if (dup2(fl2, 1) == -1 || dup2(fd[0], 0) == -1)
		(exit(write(2, "dup2 failed!\n", 13)));
	(close (fl2), close_fd(fd));
	cmd = ft_split(argv[3], ' ');
	cmd2 = ft_strjoin("/", cmd[0]);
	if (ft_checkaccess(envp, cmd2) == NULL)
	{
		(free_strings(cmd), free(cmd2));
		exit(write(2, "command not found!\n", 19));
	}
	if (execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd, envp) == -1)
	{
		free(cmd2);
		free_strings(cmd);
		exit(write(2, "Error: 2nd cmd failed!\n", 23));
	}
}

void	ft_command1(char **argv, char **envp, int fd[2])
{
	char	**cmd;
	char	*cmd2;
	int		fl;

	fl = open (argv[1], O_RDONLY, 0777);
	if (fl == -1)
		exit(write(2, "can't open the file!\n", 21));
	if (dup2(fd[1], 1) == -1 || dup2(fl, 0) == -1)
		(exit(write(2, "dup2 failed!\n", 13)), close_fd(fd), close(fl));
	close(fl);
	close_fd(fd);
	cmd = ft_split(argv[2], ' ');
	cmd2 = ft_strjoin("/", cmd[0]);
	if (ft_checkaccess(envp, cmd2) == NULL)
	{
		(free_strings(cmd), free(cmd2));
		exit(write(2, "command not found!\n", 19));
	}
	if (execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd, envp) == -1)
	{
		(free_strings(cmd), free(cmd2));
		exit(write(2, "Error: 1st cmd failed!\n", 23));
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	int	pid1;

	if (access(argv[1], F_OK) == -1)
		write(2, "No such file or directory!\n", 28);
	if (argc < 5)
		return (write (2, "Enter: <file1 cmd1 cmd2 file2!>\n", 32));
	if (pipe(fd) == -1)
		return (write(2, "Error: pipe failed!\n", 20));
	pid = fork();
	if (pid == -1)
		return (write(2, "Error: fork failed!\n", 20));
	if (pid == 0)
		ft_command1(argv, envp, fd);
	else
	{
		pid1 = fork();
		if (pid1 == -1)
			return (write(2, "Error: fork failed!\n", 20));
		if (pid1 == 0)
			ft_command2(argv, envp, fd);
	}
	close_fd(fd);
	return (wait(NULL), 0);
}
