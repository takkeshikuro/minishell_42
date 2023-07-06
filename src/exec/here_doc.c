/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:51:26 by marvin            #+#    #+#             */
/*   Updated: 2023/07/06 18:51:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_variable(char *input)
{
	int	i;

	i = 0;
	while(input[i])
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
	return(len - 1);
}

char	*get_var_name(char *input)
{
	int		i;
	int		len;
	char	*name;

	i = 1;
	len = ft_varname_len(input);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		fprintf(stderr, "ERROR MALLOC : GET VAR NAME (here_doc manage)");
		exit (1);
	}
	len = 0;
	while (input[i] != '$' && input[i] > ' '  && input[i] < 127)
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
	char	*content;
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
		//fprintf(stderr, "%s\n", envp_exp[i]);
		if (!ft_strncmp(var_name, envp_exp[i] + 11, len))
			return (envp_exp[i] + 12 + len);
		i++;
	}
	return (NULL);
}

void	here_doc_manage(t_main *data, t_cmd_parse *node, int fd[2])
{
	char	*input;
	int		size;
	int		i;
	char	*var_name;
	char	*var_content;

	while (1)
	{
		i = 0;
		input = readline(">");
		size = ft_strlen(input);
		if (!ft_strncmp(input, node->redirection->str, size) && size)
			break ;
		while (input[i])
		{
			if (input[i] == '$' && input[i + 1] != ' ')
			{
				var_name = get_var_name(input + i);
				var_content = get_var_content(data, var_name);
				if (var_content != NULL)
					write(fd[1], var_content, ft_strlen(var_content));
				i += ft_strlen(var_name) + 1;
				free(var_name);
			}
			else
			{
				write(fd[1], &input[i], 1);
				i++;
			}
		}
		write(fd[1], "\n", 1);
	}
	exit(1);
}