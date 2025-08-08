/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:36:26 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 18:37:23 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_functions(t_token **stack, t_env **env)
{
	if (ft_strcmp((*stack)->string, "echo") == 0)
		echo_command(stack);
	else if (ft_strcmp((*stack)->string, "exit") == 0)
		exit_command(stack);
	else if (ft_strcmp((*stack)->string, "pwd") == 0)
		pwd_command();
	else if (ft_strcmp((*stack)->string, "env") == 0)
		env_command(*env);
	else if (ft_strcmp((*stack)->string, "cd") == 0)
		cd_command(*stack, env);
	else if (ft_strcmp((*stack)->string, "export") == 0)
		export_command(*stack, env);
	else
		printf("%s: command not found\n", ((*stack)->string));
}