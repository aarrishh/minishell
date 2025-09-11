/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:26:03 by arina             #+#    #+#             */
/*   Updated: 2025/09/11 19:32:20 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_tsilda_to_home(char *str, t_env *env)
{
	char	*home;
	char	*target;
	char	*result;

	home = ft_strdup(ft_strchr(str, '/'));
	target = get_env_value(env, "HOME");
	if (home)
		result = ft_strjoin(target, home);
	else
		return (target);
	free(home);
	return (result);
}

void	cd_command(t_token *stack, t_env **env)
{
	char	*old_pwd;
	char	*target;

	old_pwd = get_env_value(*env, "PWD");
	if (!stack->next)
		target = get_env_value(*env, "HOME");
	else if (ft_strcmp(stack->next->string, "-") == 0)
		target = get_env_value(*env, "OLDPWD");
	else if (stack->next->string[0] == '~')
		target = change_tsilda_to_home(stack->next->string, *env);
	else
		target = stack->next->string;
	if (!target || chdir(target) != 0)
	{
		print_cd_error(target);
		g_exit_status = 1;
		return ;
	}
	update_env_new_and_old_pwd(env, old_pwd);
	g_exit_status = 0;
	if (stack->next && stack->next->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_exit_status = 1;
	}
}
