/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/09/06 18:57:09 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

void	init_data(t_data *data, char **envp)
{
	data->stack = NULL;
	data->split = NULL;
	data->env = add_env_to_list(envp);
}

void	handle_cmds(t_data *data)
{
	if (data->stack && has_operator(data->stack, PIPE))
		execute_pipe(data);
	else if (data->stack && (has_operator(data->stack, REDIR_IN)
			|| has_operator(data->stack, REDIR_OUT) || has_operator(data->stack,
				APPEND) || has_operator(data->stack, HEREDOC)))
		operators(data, data->stack);
	else if (data->stack)
	{
		if (is_builtin_cmd((*data->stack).string))
			built_in_functions(data, (*data->stack).string);
		else
			execute_else(&data->env, &data->stack->string);
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
		if (line && line[0] != '\0') // && !is_space(line))
			add_history(line);
		if (!line)
		{
			// free_all(&data.env, &data.stack, data.split);
			handle_ctrl_d();
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (!start_dquotes(line, &data))
			continue ;
		if (data.split)
			validation(data.split, &data.stack, &data.env);
		init_tokens_type(&data.stack);
		handle_cmds(&data);
		free_all(NULL, &data.stack, data.split);
		free(line);
	}
	return (0);
}
