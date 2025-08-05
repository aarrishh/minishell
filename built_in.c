/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:14 by arina             #+#    #+#             */
/*   Updated: 2025/08/05 17:53:25 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_check(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (-1);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}

void	*echo_command(t_token **stack)
{
	t_token *tmp;
	int	flag;

	flag = 0;
	if (!(*stack)->next)
		return(printf("\n"), "");
	tmp = (*stack)->next;
	while (tmp && ft_strncmp(tmp->string, "-n", 2) == 0)
	{
		flag = 1;
		if (n_check(tmp->string) == -1)
		{	
			flag = 0;
			break ;
		}
		else
			tmp = tmp->next;
	}
	while (tmp && tmp->next)
	{
		printf("%s ", tmp->string);
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (flag == 1)
			printf("%s", tmp->string);
		else
			printf("%s\n", tmp->string);
	}
	return ("");
}

int	exit_command(t_token **stack)
{
	t_token		*tmp;
	long long	num;
	int			flag;

	num = 0;
	flag = 0;
	tmp = (*stack);
	if (tmp->next)
	{
		tmp = tmp->next;
		flag = ft_atol(tmp->string, &num);
		if (flag == -1)
			printf("exit\nbash: exit: %s: numeric argument required\n", \
			tmp->string), exit(2);
	}
	if (tmp->next)
		return (printf("exit\nbash: exit: too many arguments\n"), 1);
	else
		printf("exit\n"), exit(num % 256);
	return (0);
}

void	pwd_command(void)
{
	char *dest;

	dest = getcwd(NULL, 0);
	if (!dest)
		return ;
	printf("%s\n", dest);
	free (dest);
}

void	env_command(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	cd_command(t_token *stack, t_env **env)
{
	char	*path;
	char	*cur_dir;

	cur_dir = NULL;
	path = NULL;
	stack = stack->next;
	if (stack == NULL || stack->string == NULL)
		path = get_env_value(*env, "HOME");
	else
		path = stack->string;
	if (chdir(path) == -1)
		perror("cd");
	cur_dir = getcwd(NULL, 0);
	// if (cur_dir)
	// {
	// 	printf("cd -> %s\n", cur_dir);
	// 	free(cur_dir);
	// }
}

void	sort_env(t_env **env)
{
	t_env	*tmp;
	t_env	*idk;
	char	*temp;

	tmp = *env;
	while (tmp && tmp->next)
	{
		idk = tmp->next;
		while (idk)
		{
			if (ft_strcmp(tmp->key, idk->key) > 0)
			{
				temp = tmp->key;
				tmp->key = idk->key;
				idk->key = temp;
				temp = tmp->value;
				tmp->value = idk->value;
				idk->value = temp;
			}
			idk = idk->next;
		}
		tmp = tmp->next;
	}
}

void	export_command(t_token *stack, t_env **env)
{
	t_env	*tmp_env;
	t_env	*node;

	tmp_env = *env;

	while (stack->next)
	{
		stack = stack->next;
		if (find_equal(stack->string) != -1)
			node = new_node(ft_substr(stack->string, 0, find_equal(stack->string)), ft_strdup(ft_strchr(stack->string, '=') + 1));
		else
			node = new_node(stack->string, "");
		env_add_back(node, env);
	}
	sort_env(env);
	tmp_env = *env;
	while (tmp_env)
	{
		printf("declare -x %s=\"%s\"\n", tmp_env->key, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	printf("-------------------------------------------------------------------------------------------\n");
}

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
