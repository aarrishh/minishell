/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:36:26 by arina             #+#    #+#             */
/*   Updated: 2025/09/13 13:59:57 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_shlvl_value(t_env **env, char **cmd)
{
	t_env	*tmp;
	int		res;

	tmp = *env;
	res = 0;
	if (ft_strcmp(cmd[0], "./minishell") == 0 && cmd[1] == NULL)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "SHLVL") == 0)
			{
				if (tmp->value)
					res = ft_atoi(tmp->value);
				free(tmp->value);
				tmp->value = ft_itoa(res + 1);
				return ;
			}
			tmp = tmp->next;
		}
	}
}

int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	built_in_functions(t_data *data, t_token **stack, char *string)
{
	if (ft_strcmp(string, "echo") == 0)
		echo_command(stack);
	else if (ft_strcmp(string, "exit") == 0)
		exit_command(stack, &data->env, data->split);
	else if (ft_strcmp(string, "pwd") == 0)
		pwd_command();
	else if (ft_strcmp(string, "env") == 0)
		env_command(data->env, *stack);
	else if (ft_strcmp(string, "cd") == 0)
		cd_command(*stack, &data->env);
	else if (ft_strcmp(string, "export") == 0)
		export_command(data, *stack);
	else if (ft_strcmp(string, "unset") == 0)
		unset_command(data);
}
