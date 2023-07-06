/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:50:38 by marvin            #+#    #+#             */
/*   Updated: 2023/07/06 18:50:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_exec_3(t_main *data, t_cmd_parse *node, char *cmd)
{
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
	{
		built_unset(data, node);
		exit (1);	
	}
}

void	builtin_exec_2(t_main *data, t_cmd_parse *node, char *cmd)
{
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
	{
		exit (1);	
	}
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
	{
		built_export(data, node);
		exit (1);
	}
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
	{
		built_pwd(data, node);
		exit (1);
	}
	else
	builtin_exec_3(data, node, cmd);
}
void	builtin_exec(t_main *data, t_cmd_parse *node)
{
	char	*cmd;

	cmd = node->cmd_tab[0];
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
	{
		built_cd(data, node);
		exit (1);	
	}
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
	{
		built_echo(data, node);
		exit (1);
	}
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
	{
		built_env(data, node);
		exit (1);
	}
	else
		builtin_exec_2(data, node, cmd);
}