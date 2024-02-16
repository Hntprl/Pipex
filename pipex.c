/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:16:27 by amarouf           #+#    #+#             */
/*   Updated: 2024/02/16 02:45:17 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *ft_findpath(char **envp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (envp[i] != NULL)
    {
        if (ft_strnstr(envp[i], "PATH", 4) != NULL)
            return ((envp[i] + 5));
        i ++;
    }
    return (NULL);
}

char *ft_checkaccess(char **envp, char *cmd)
{
    int i;
    char **allpaths;
    char *path;

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

void ft_command2(char **argv, char **envp, int fd[2])
{
    char **cmd;
    char *cmd2;
    int fl2;

    if (!argv[2][0] || !argv[3][0])
    {
        write(2, "Enter a command!\n", 17);
        exit(EXIT_FAILURE);
    }
    fl2 = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (fl2 == -1)
        exit(EXIT_FAILURE);
    dup2(fd[0], 0);
    dup2(fl2, 1);
    close (fl2);
    close_fd(fd);
    cmd = ft_split(argv[3], ' ');
    cmd2 = ft_strjoin("/", cmd[0]);
    if (!cmd || !cmd2)
        exit(EXIT_FAILURE);
    if (execve(ft_strjoin(ft_checkaccess(envp , cmd2), cmd2), cmd, envp) == -1)
       exit(EXIT_FAILURE);
}

void ft_command1(char **argv, char **envp, int fd[2])
{
    char **cmd;
    char *cmd2;
    int fl;

    fl = open (argv[1], O_RDONLY, 0777);
    if (fl == -1)
        exit(EXIT_FAILURE);
    dup2(fl, 0);
    close(fl);
    dup2(fd[1], 1);
    close_fd(fd);
    cmd = ft_split(argv[2], ' ');
    cmd2 = ft_strjoin("/", cmd[0]);
    if (!cmd || !cmd2)
        exit(EXIT_FAILURE);
    if (execve(ft_strjoin(ft_checkaccess(envp , cmd2), cmd2), cmd, envp) == -1)
        exit(EXIT_FAILURE);
}

int main (int argc, char **argv, char **envp)
{
    int fd[2];
    int pid;
    int pid1;

    if(access(argv[1], F_OK) == -1)
        exit(write(2, "No such file or directory!\n", 28));
    if (argc < 5)
       return (write(2,"Enter: <file1 cmd1 cmd2 file2!>\n", 32));
    if (pipe(fd) == -1)
        return (1);
    pid = fork();
    if (pid == -1)
        return (2);
    if (pid == 0)
        ft_command1(argv, envp, fd);
    else
    {
        pid1 = fork();
        if (pid1 == -1)
            return (2);
        if (pid1 == 0)
        ft_command2(argv, envp, fd);
    }
    close_fd(fd);
    wait(NULL);
    return (0);
}