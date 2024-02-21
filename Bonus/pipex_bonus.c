/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:57:49 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/21 13:43:20 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_checkaccess(char **envp, char *cmd)
{
	int		i;
	char	**allpaths;
	char	*path;

	i = 0;
	allpaths = ft_split(ft_findpath(envp), ':');
	if (allpaths == NULL)
		exit(EXIT_FAILURE);
	while (allpaths[i] != NULL)
	{
		if (access(ft_strjoin(allpaths[i], cmd), F_OK) == 0)
		{
			path = malloc(ft_strlen(allpaths[i]));
			if (path == NULL)
				exit(EXIT_FAILURE);
			path = ft_strdup(allpaths[i]);
			return (ft_free(allpaths), path);
		}
		i ++;
	}
	ft_free(allpaths);
	write(2, "Command not found !\n", 20);
	return (NULL);
}

void	ft_first_command(char **argv, char **envp, int fd[2])
{
	char	**cmd1;
	char	*cmd2;
	int		fl;

	if (fork() == 0)
	{
		fl = open (argv[1], O_RDONLY);
		if (fl == -1)
			(exit(write(2, "can't open the file!\n", 21)), close_fd(fd));
		(dup2(fl, 0), dup2(fd[1], 1));
		(close_fd(fd), close(fl));
		cmd1 = ft_split(argv[2], ' ');
		cmd2 = ft_strjoin("/", cmd1[0]);
		if (!cmd2)
			exit(write (2, "Wrong Command!\n", 15));
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}

void	ft_all_commands(char *cmd, char **envp, int fd[2])
{
	char	**cmd1;
	char	*cmd2;

	if (fork() == 0)
	{
		if (dup2(fd[1], 1) == -1)
			(exit(write(2, "all commands: dup2 failed!\n", 27)), close_fd(fd));
		close_fd(fd);
		cmd1 = ft_split(cmd, ' ');
		cmd2 = ft_strjoin("/", cmd1[0]);
		if (!cmd || !cmd2)
			(exit(write (2, "Wrong Command!\n", 15)), close_fd(fd));
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}

void	ft_last_command(char **argv, char **envp, int argc, int fd[2])
{
	char	*cmd;
	char	**cmd1;
	char	*cmd2;
	int		fl;

	cmd = argv[argc - 2];
	if (fork() == 0)
	{
		fl = open (argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fl == -1)
			(exit(write(2, "Open: Can't open The file!\n", 27)), close_fd(fd));
		(dup2(fl, 1), close(fl));
		cmd1 = ft_split(cmd, ' ');
		cmd2 = ft_strjoin("/", cmd1[0]);
		if (!cmd || !cmd2)
			(exit(write (2, "Wrong Command!\n", 15)), close_fd(fd));
		close_fd(fd);
		execve(ft_strjoin(ft_checkaccess(envp, cmd2), cmd2), cmd1, envp);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	var.i = 2;
	if (argc < 5 || pipe(var.fd) == -1)
		return (write (2, "Enter: <file1 cmd1 cmd2 file2!>\n", 32));
	if (!ft_strncmp(argv[1], "here_doc", 8))
		(ft_here_dock(argc, argv, var.fd), close(var.fd[1]));
	else
		(ft_first_command(argv, envp, var.fd), close(var.fd[1]));
	var.input = var.fd[0];
	while (var.i < argc - 3)
	{
		if (dup2 (var.input, 0) == -1)
			(close_fd(var.fd), exit(write(2, "Dup2 Error: input dup\n", 22)));
		close(var.input);
		if (pipe(var.fd) == -1)
			exit(write(2, "Pipe Error: The 2nd pipe failed!\n", 28));
		ft_all_commands(argv[++ var.i], envp, var.fd);
		(close (var.fd[1]), var.input = var.fd[0]);
	}
	if (dup2(var.input, 0) == -1)
		(exit(write (2, "Dup2: dup2 failed!\n", 19)), close(var.input));
	(close(var.input), ft_last_command(argv, envp, argc, var.fd), close(0));
	while (wait(NULL) == -1)
		;
}
