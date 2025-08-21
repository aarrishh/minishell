/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/08/21 13:39:50 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Count how many nodes are in env
static int	env_size(t_env *env)
{
	int count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

// Join key=value into one string
static char	*join_key_value(char *key, char *value)
{
	int		len;
	char	*str;

	if (!value) // case: key with no value (e.g. "PATH=")
		value = "";
	len = strlen(key) + 1 + strlen(value) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	strcpy(str, key);
	strcat(str, "=");
	strcat(str, value);
	return (str);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = join_key_value(env->key, env->value);
		if (!envp[i])
		{
			// free previously allocated strings if malloc fails
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}


void	init_data(t_data *data, char **envp)
{
	data->stack = NULL;
	data->split = NULL;
	data->envp = envp;
	data->env = add_env_to_list(envp);
}

void	handle_cmds(t_data *data)
{
	if (data->stack && has_operator(data->stack, PIPE))
		execute_pipe(data);
	else if (data->stack && has_operator(data->stack, REDIR_OUT))
		redir_function(data, 0); // chka es exit_status
	else if (has_operator(data->stack, APPEND))
		redir_function(data, 1); // chka es exit_status
	else if (has_operator(data->stack, REDIR_IN))
		redir_in(data);
	else if (has_operator(data->stack, HEREDOC))
		printf("not done yet\n");
	else if (data->stack)
	{
		if (is_builtin_cmd((*data->stack).string, &data->env, data->stack))
			built_in_functions(&data->stack, (*data->stack).string, &data->env,
				data->split);
		else
			execute_else(&data->env, data->split);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	(void)argc;
	(void)argv;
	setup_signals();
	init_data(&data, envp);
	while (1)
	{
		line = readline("🌸 " PB "minishell" R " " W "✦" R " ");
		if (line)
			add_history(line);
		if (!line)
			handle_ctrl_d();
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (!start_quotes(line, &data))
			continue ;
		if (data.split)
			validation(data.split, &data.stack);
		init_tokens_type(&data.stack);
		// change_shlvl_value(&data.env, data.stack);
		handle_cmds(&data);
		free_all(NULL, &data.stack, data.split);
		free(line);
	}
	rl_clear_history();
	return (0);
}
