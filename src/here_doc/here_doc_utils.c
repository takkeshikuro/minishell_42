/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:38:28 by rmarecar          #+#    #+#             */
/*   Updated: 2023/09/01 19:36:07 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_variable(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_varname_len(char *str)
{
	int	len;

	len = 1;
	while (str[len] > ' ' && str[len] < 127 && str[len] != '$')
		len++;
	return (len - 1);
}

char	*get_var_name(t_main *data, char *input)
{
	int		i;
	int		len;
	char	*name;

	i = 1;
	len = ft_varname_len(input);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		printf("ERROR MALLOC : GET VAR NAME (here_doc manage)");
		free_tab(data->cmd_paths);
		free_tab(data->env_bis);
		free_tab(data->env_exp);
		reset_stuff(data);
		exit (1);
	}
	len = 0;
	while (input[i] != '$' && input[i] > ' ' && input[i] < 127)
	{
		name[len] = input[i];
		i++;
		len++;
	}
	name[len] = 0;
	return (name);
}

char	*get_var_content(t_main *data, char *var_name)
{
	int		i;
	char	**envp;
	char	**envp_exp;
	int		len;

	len = ft_strlen(var_name);
	i = 0;
	envp = data->env_bis;
	envp_exp = data->env_exp;
	while (envp[i])
	{
		if (!ft_strncmp(var_name, envp[i], len))
			return (envp[i] + len + 1);
		i++;
	}
	i = 0;
	while (envp_exp[i])
	{
		if (!ft_strncmp(var_name, envp_exp[i] + 11, len))
			return (envp_exp[i] + 12 + len);
		i++;
	}
	return (NULL);
}

int	here_doc_var(t_main *data, char *input, int i, int fd[2])
{
	char	*var_name;
	char	*var_content;
	int		len;

	var_name = get_var_name(data, input + i);
	var_content = get_var_content(data, var_name);
	if (var_content != NULL)
		write(fd[1], var_content, ft_strlen(var_content));
	len = ft_strlen(var_name) + 1;
	free(var_name);
	return (len);
}
