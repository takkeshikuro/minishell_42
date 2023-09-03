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

void	builtin_exec_3(t_main *data, t_cmd_parse *node, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "unset", len) && len == 5)
	{
		built_unset(data, node);
		built_in_free(data);
		exit(data->return_value);
	}
	if (contains_char(cmd, '=') && cmd[0] != '=')
	{
		add_v_to_hidetab(data, cmd);
		built_in_free(data);
		exit(data->return_value);
	}
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
	{
		built_echo(data, node);
		built_in_free(data);
		exit (data->return_value);
	}
}

void	builtin_exec_2(t_main *data, t_cmd_parse *node, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "exit", len) && len == 4)
	{
		built_in_free(data);
		exit (data->return_value);
	}
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
	{
		built_export(data, node);
		built_in_free(data);
		exit (data->return_value);
	}
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
	{
		built_pwd(data, node);
		built_in_free(data);
		exit (data->return_value);
	}
	else
		builtin_exec_3(data, node, cmd, len);
}

void	builtin_exec(t_main *data, t_cmd_parse *node)
{
	char	*cmd;
	int		len;

	if (node->cmd_tab[0] == NULL)
		return ;
	cmd = node->cmd_tab[0];
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", len) && len == 2)
	{
		built_cd(data, node);
		built_in_free(data);
		exit (data->return_value);
	}
	else if (!ft_strncmp(cmd, "env", len) && len == 3)
	{
		built_env(data, node);
		built_in_free(data);
		exit (data->return_value);
	}
	else
		builtin_exec_2(data, node, cmd, len);
}

int	first_builtins2(t_main *data, t_cmd_parse *node, int len)
{
	if (data->pipe_count == 0 && contains_char(node->cmd_tab[0], '=')
		&& node->cmd_tab[0][0] != '=')
	{
		add_v_to_hidetab(data, node->cmd_tab[0]);
		return (1);
	}
	if (!ft_strncmp(node->cmd_tab[0], "unset", len) && node->next == NULL
		&& len == 5)
		return (built_unset(data, node));
	if (!ft_strncmp(node->cmd_tab[0], "export", len) && node->next == NULL
		&& len == 6)
		return (built_export(data, node));
	if (!ft_strncmp(node->cmd_tab[0], "cd", len) && node->next == NULL
		&& len == 2)
	{
		if (data->pipe_count)
			return (0);
		return (built_cd(data, node));
	}
	return (0);
}

int	first_builtins(t_main *data, t_cmd_parse *node)
{
	int	len;

	if (node->cmd_tab[0])
		len = ft_strlen(node->cmd_tab[0]);
	if (node->cmd_tab[0] == NULL)
		return (0);
	if (first_builtins2(data, node, len))
		return (1);
	if (!ft_strncmp(node->cmd_tab[0], "exit", len) && len == 4)
	{
		if (data->pipe_count)
			return (0);
		data->return_value = built_exit(data, node);
		return (1);
	}
	return (0);
}
