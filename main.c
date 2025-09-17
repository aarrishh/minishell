/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/09/17 21:41:03 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "quotes/quotes.h"

int		g_exit_status = 0;

void	init_data(t_data *data, char **envp, char **argv, int argc)
{
	(void)argv;
	(void)argc;
	data->stack = NULL;
	data->split = NULL;
	data->env = add_env_to_list(envp);
}

void	execute_else(t_env **env, char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_process_execution(env, cmd);
	else
		parent_process_handling(pid, &status, cmd);
	free_array(cmd);
}

void	handle_cmds(t_data *data)
{
	char	**cmd;
	t_token	*tmp;

	tmp = data->stack;
	cmd = NULL;
	if (data->stack && has_operator(data->stack, PIPE))
		execute_pipe(data);
	else if (data->stack && (has_operator(data->stack, REDIR_IN)
			|| has_operator(data->stack, REDIR_OUT) || has_operator(data->stack,
				APPEND) || has_operator(data->stack, HEREDOC)))
		operators(data, data->stack);
	else if (data->stack)
	{
		if (is_builtin_cmd((*data->stack).string))
			built_in_functions(data, &data->stack, (*data->stack).string);
		else
		{
			while (tmp)
			{
				cmd = add_arg_to_cmd(cmd, tmp->string);
				tmp = tmp->next;
			}
			execute_else(&data->env, cmd);
		}
	}
}

void	start(char *line, t_data *data)
{
	start_dquotes(line, data);
	validation(data->split, &data->stack, &data->env);
	init_tokens_type(&data->stack);
	handle_cmds(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	setup_signals();
	init_data(&data, envp, argv, argc);
	while (1)
	{
		line = readline("🌸 " PB "minishell" R " " W "✦" R " ");
		if (line && line[0] != '\0')
			add_history(line);
		if (!line)
		{
			free_all(&data.env, NULL, NULL);
			handle_ctrl_d();
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		start(line, &data);
		free(line);
		free_all(NULL, &data.stack, data.split);
	}
	return (0);
}
