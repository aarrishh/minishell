/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:36:26 by arina             #+#    #+#             */
/*   Updated: 2025/08/11 13:59:00 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_functions(t_token **stack, char *string, t_env **env)
{
	if (ft_strcmp(string, "echo") == 0)
		echo_command(stack);
	else if (ft_strcmp(string, "exit") == 0)
		exit_command(stack);
	else if (ft_strcmp(string, "pwd") == 0)
		pwd_command();
	else if (ft_strcmp(string, "env") == 0)
		env_command(*env);
	else if (ft_strcmp(string, "cd") == 0)
		cd_command(*stack, env);
	else if (ft_strcmp(string, "export") == 0)
		export_command(*stack, env);
	else if (ft_strcmp(string, "unset") == 0)
		unset_command(*stack, env);
}
