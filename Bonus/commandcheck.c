/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:46:50 by amarouf           #+#    #+#             */
/*   Updated: 2024/03/06 23:08:50 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	commandcheck(char **envp, char *cmd2, char **cmd1)
{
	if (ft_checkaccess(envp, cmd2) == NULL)
	{
		(free_strings(cmd1), free(cmd2));
		exit(write(2, "command not found!\n", 19));
	}
}
