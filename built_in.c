/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:14 by arina             #+#    #+#             */
/*   Updated: 2025/08/06 11:07:27 by mabaghda         ###   ########.fr       */
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
	t_token	*tmp;
	int		flag;

	flag = 0;
	if (!(*stack)->next)
		return (printf("\n"), "");
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
			printf("exit\nbash: exit: %s: numeric argument required\n",
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
		printf("%s = %s\n", env->key, env->value);
		env = env->next;
	}
}

// char	*remove_last_dest(char *str)
// {
// 	int		i;
// 	int		start;
// 	char	*copy;

// 	i = 0;
// 	start = 0;
// 	while (str[i])
// 		i++;
// 	while (str[i] != '/')
// 		i--;
// 	copy = (char *)malloc((i + 1) * sizeof(char));
// 	while (start < i)
// 	{
// 		copy[start] = str[start];
// 		start++;
// 	}
// 	copy[start] = '\0';
// 	printf("-----------------------%s\n", copy);
// 	return(copy);
// }

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
	if (cur_dir)
	{
		printf("cd -> %s\n", cur_dir);
		free(cur_dir);
	}
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
	else
		printf("%s: command not found\n", ((*stack)->string));
}
