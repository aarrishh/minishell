/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:14 by arina             #+#    #+#             */
/*   Updated: 2025/08/07 17:40:24 by arimanuk         ###   ########.fr       */
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
	free (dest); // avelacnel vor env-i mej poxi PWD-value-n chisht dir-ov
}

void	env_command(t_env *env)
{
	while (env)
	{
		if ((ft_strcmp(env->value, "") != 0) || (ft_strcmp(env->value, "") == 0 && env->flag == 1))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	printf("--------------------------------------------------------------------\n");
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
}

t_env	*sort_env(t_env *env)
{
	t_env	*idk;
	char	*temp;
	int		flag_tmp;

	while (env && env->next)
	{
		idk = env->next;
		while (idk)
		{
			if (ft_strcmp(env->key, idk->key) > 0)
			{
				temp = env->key;
				env->key = idk->key;
				idk->key = temp;
				temp = env->value;
				env->value = idk->value;
				idk->value = temp;
				flag_tmp = env->flag;
				env->flag = idk->flag;
				idk->flag = flag_tmp;
				
			}
			idk = idk->next;
		}
		env = env->next;
	}
	return (env);
}

int	find_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (i);
		i++;
	}
	return (-1);
}

int	check_sameness(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(ft_substr(str, 0, find_equal(str)), "_") == 0)
			return (0);
		else if (ft_strcmp(ft_substr(str, 0, find_equal(str)), env->key) == 0)
			return (1);
		else if ((find_equal_for_export(str) == -2) && ft_strcmp(ft_substr(str, 0, find_plus(str)), env->key) == 0)
			return (2);
		// else if ((ft_strcmp(ft_substr(str, 0, find_equal(str)), env->key) == 0) && \
		// 	ft_strcmp(ft_substr(str, find_equal(str), 2), "+=") == 0)
		// 	return (2);
		env = env->next;
	}
	return (0);
}

void	change_value(char *str, t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(ft_substr(str, 0, find_equal(str)), tmp->key) == 0)
		{
			printf("ha vor=%d\n", tmp->flag);
			free(tmp->value);
			tmp->value = ft_strdup(ft_strchr(str, '=') + 1);
			
			break ;
		}
		tmp = tmp->next;
	}
}

void	check_i_have_value_after_equal_symbol(int index, char *str, t_env **node)
{
	if (ft_strcmp(ft_substr(str, 0, find_equal(str)), (*node)->key) == 0)
	{
		if (str[index + 1] == '\0')
			(*node)->flag = 1;
		return ;
	}
}

void	check_i_have_value_after_equal_symbol_version_two(int index, char *str, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(ft_substr(str, 0, find_equal(str)), tmp->key) == 0)
		{
			if (str[index + 1] == '\0')
				tmp->flag = 1;
			else
				tmp->flag = 0;
			return ;
		}
		tmp = tmp->next;
	}
}

int	find_plus_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	find_equal_for_export(char *str)
{
	int	i;

	i = 0;
	if (find_plus_equal(str) != -1)
		return (-2);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (ft_strcmp(key, "_") == 0)
		return (-1);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (-1);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

void	change_value_for_plus_equal_case(char *str, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(ft_substr(str, 0, find_plus(str)), tmp->key) == 0)
			tmp->value = ft_strjoin(tmp->value, ft_strdup(ft_strchr(str, '=') + 1));
		tmp = tmp->next;
	}
}

void	print_error_export(char *str)
{
	printf("bash: export: `%s': not a valid identifier\n", str);
}

void	print_export(t_env *env)
{
	// t_env *tmp_env;

	// tmp_env = copy_env_list(env);
	env = sort_env(env);
	while (env)
	{
		if (ft_strcmp(env->value, "") == 0 && env->flag == 0)
			printf("declare -x %s\n", env->key);
		else
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

void	export_command(t_token *stack, t_env **env)
{
	t_env	*node;
	// t_token *tmp;

	// tmp = stack;
	node = NULL;
	if (stack->next == NULL)
	{
		print_export(*env);
		return ;
	}
	while (stack->next)
	{
		stack = stack->next;
		if (find_equal_for_export(stack->string) >= 0) // = a gtel
		{
			if (check_sameness(stack->string, *env) == 0)
			{
				// printf("che stex mta\n");
				if (check_key(ft_substr(stack->string, 0, find_equal(stack->string))) == -1)
				{
					node = NULL;
					print_error_export(stack->string);
				}
				else
				{
					node = new_node(ft_substr(stack->string, 0, find_equal(stack->string)), ft_strdup(ft_strchr(stack->string, '=') + 1));
					check_i_have_value_after_equal_symbol(find_equal(stack->string), stack->string, &node);
				}
			}
			else
			{
				// printf("stex mta?\n");
				change_value(stack->string, env);
				check_i_have_value_after_equal_symbol_version_two(find_equal(stack->string), stack->string, env);
			}
		}
		else if (find_equal_for_export(stack->string) == -2) // += a gtel
		{
			// printf("che che stex mta\n");
			if (check_sameness(stack->string, *env) == 2) // u ka env-um
				change_value_for_plus_equal_case(stack->string, env);
			else
				node = new_node(ft_substr(stack->string, 0, find_plus(stack->string)), ft_strdup(ft_strchr(stack->string, '=') + 1));
		}
		else // chka vochmiban
		{
			// printf("che che che stex mta\n");
			if (check_sameness(stack->string, *env) == 0)
				node = new_node(stack->string, ft_strdup(""));
			else
				continue;
		}
		if (node)
			env_add_back(node, env);
	}
	// if (tmp->next == NULL)
	// 	print_export(*env);
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
