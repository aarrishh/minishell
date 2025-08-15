/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/08/15 19:05:26 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	init_data(t_data *data, char **envp)
{
	data->stack = NULL;
	data->split = NULL;
	data->envp = envp;
	data->env = add_env_to_list(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	(void)argc, (void)argv;
	// rl_catch_signals = 0;
	// rl_clear_history();
	// setup_signals();
	init_data(&data, envp);
	while (1)
	{
		line = readline("🌸 " PB "minishell" R " " W "✦" R " ");
		if (line)
			add_history(line);
		if (!line)
		{
			// handle_ctrl_d();
			break ;
		}
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
		if (data.stack && has_pipe(data.stack))
			execute_pipe(&data);
		else if (data.stack)
		{
			if (is_builtin_cmd((*data.stack).string))
				built_in_functions(&data.stack, (*data.stack).string, &data.env,
					data.split);
			else
				execute_else(&data.env, data.split, envp);
		}
		free_stack(&data.stack);
		free(line);
		free_array(data.split);
	}
	return (0);
}
