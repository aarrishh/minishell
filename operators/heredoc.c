/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:08:04 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/16 16:14:16 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_heredoc_loop(t_env **env, char *delimiter, int i)
{
	char	*filename;
	char	*line;
	int		fd;

	filename = create_file(i, &fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_ctrl_d();
			break ;
		}
		if (check_dollar_hd(line))
			line = expand_heredoc(&line, env);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (filename);
}

int	heredoc_expand_len(char *line, t_env **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
			handle_len_dollar(line, &i, &len, env);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*expand_heredoc(char **line, t_env **env)
{
	char		*new;
	t_new_line	line_st;
	int			len;

	len = heredoc_expand_len(*line, env);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	line_st.line = *line;
	line_st.new = new;
	line_st.i = 0;
	line_st.j = 0;
	while (line_st.line[line_st.i])
	{
		if (line_st.line[line_st.i] == '$')
			handle_dollar(&line_st, env);
		else
			keep_char(&line_st);
	}
	line_st.new[line_st.j] = '\0';
	free(*line);
	return (new);
}

int	check_dollar_hd(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	handle_heredoc(t_data *data, t_command *cmd_struct, t_token **tmp,
		int i)
{
	char	*delim;
	char	*filename;
	pid_t	pid;
	int		status;

	filename = NULL;
	if (!(*tmp)->next || !(*tmp)->next->string || !*(*tmp)->next->string)
		delim = "";
	else
		delim = (*tmp)->next->string;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		filename = read_heredoc_loop(&data->env, delim, i);
		exit(0);
	}
	else
	{
		wait_sig_hd(pid, &status);
		wait_hereoc(cmd_struct, filename, i);
	}
}
