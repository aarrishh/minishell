/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:36:26 by arina             #+#    #+#             */
/*   Updated: 2025/08/18 20:40:30 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	built_in_functions(t_token **stack, char *string, t_env **env,
		char **split)
{
	if (ft_strcmp(string, "echo") == 0)
		echo_command(stack);
	else if (ft_strcmp(string, "exit") == 0)
		exit_command(stack, env, split);
	else if (ft_strcmp(string, "pwd") == 0)
		pwd_command();
	else if (ft_strcmp(string, "env") == 0)
		env_command(*env, *stack);
	else if (ft_strcmp(string, "cd") == 0)
		cd_command(*stack, env);
	else if (ft_strcmp(string, "export") == 0)
		export_command(*stack, env);
	else if (ft_strcmp(string, "unset") == 0)
		unset_command(*stack, env);
}
