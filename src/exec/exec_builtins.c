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
		exit(data->return_value);
	}
	if (contains_char(cmd, '=') && cmd[0] != '=')
	{
		add_v_to_envexp(data, cmd);
		exit(data->return_value);
	}
}

void	builtin_exec_2(t_main *data, t_cmd_parse *node, char *cmd)
{
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
	{
		exit (data->return_value);
	}
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
	{
		built_export(data, node);
		exit (data->return_value);
	}
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
	{
		built_pwd(data, node);
		exit (data->return_value);
	}
	else
		builtin_exec_3(data, node, cmd);
}

void	builtin_exec(t_main *data, t_cmd_parse *node)
{
	char	*cmd;

	if (node->cmd_tab[0] == NULL)
		return ;
	cmd = node->cmd_tab[0];

	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
	{
		built_echo(data, node);
		exit (data->return_value);
	}
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
	{
		built_env(data, node);
		exit (data->return_value);
	}
	else
		builtin_exec_2(data, node, cmd);
}

int	first_builtins2(t_main *data, t_cmd_parse *node)
{
	if (data->pipe_count == 0 && contains_char(node->cmd_tab[0], '=')
		&& node->cmd_tab[0][0] != '=')
	{
		add_v_to_envexp(data, node->cmd_tab[0]);
		return (1);
	}
	return (0);
}

int	first_builtins(t_main *data, t_cmd_parse *node)
{
	int	len;

	if (node->cmd_tab[0] == NULL)
		return (0);
	if (first_builtins2(data, node))
		return (1);
	if (node->cmd_tab[0])
		len = ft_strlen(node->cmd_tab[0]);
	if (!ft_strncmp(node->cmd_tab[0], "exit", len) && len)
	{
		built_exit(data, node);
		return (1);
	}
	if (!ft_strncmp(node->cmd_tab[0], "unset", len) && node->next == NULL)
		return (built_unset(data, node));
	if (!ft_strncmp(node->cmd_tab[0], "export", len) && node->next == NULL)
		return (built_export(data, node));
	if (!ft_strncmp(node->cmd_tab[0], "cd", len) && node->next == NULL)
		return (built_cd(data, node));
	return (0);
}
