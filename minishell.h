/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:31:11 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/16 18:14:42 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "quotes/quotes.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PB "\001\033[1;38;2;255;204;213m\002" // bold pink
# define W "\001\033[38;2;255;255;255m\002"    // white
# define R "\001\033[0m\002"                   // reset

extern int	g_exit_status;

typedef struct s_val
{
	char	*substr;
	char	*expanded;
	int		cur_ind;
	int		i;
	int		j;
}			t_val;

typedef struct s_pipe_fd
{
	int		prev_fd;
	int		pfd[2];
	int		last_cmd;
}			t_pipe_fd;

typedef struct s_command
{
	char	**cmd;
	int		execute;
	int		input;
	int		output;
	char	*heredoc;
}			t_command;

// Operations functions
char		*create_file(int i, int *fd);
void		wait_hereoc(t_command *cmd_struct, char *filename, int i);
void		wait_sig_hd(pid_t pid, int *status);
int			check_syntax(t_token *stack);
void		execute_pipe(t_data *data);
char		*get_first_word(t_token *tmp);
int			fork_and_get_cmd(t_data *data, t_pipe_fd *fds, t_token **tmp);
void		execute_else(t_env **env, char **cmd);
char		*split_path(t_env **env, char *cmd);
int			has_operator(t_token *stack, t_token_type type);
void		execute_command(t_data *data, t_command *cmd_struct);
int			two_dim_len(char **str);
void		handle_heredoc(t_data *data, t_command *cmd_struct, t_token **tmp,
				int i);
void		read_from_file(t_env **env, char *filename, char **cmd);
int			check_dollar_hd(char *line);
char		*expand_heredoc(char **line, t_env **env);
int			count_segments(t_token **stack, t_token_type type);
char		**add_arg_to_cmd(char **cmd_arg, char *str);
int			find_and_open(char *filename, t_token_type type);
void		read_heredoc_loop(t_env **env, char *delimiter, int i,
				char **filename);
int			operators(t_data *data, t_token *stack);
void		error_nl_or_type(t_command *cmd_s, t_token *tmp);
void		redirs_child(t_data *data, t_command *cmd_struct);
void		builtin_redirs(t_command *cmd_struct, int *saved_in,
				int *saved_out);
void		restore_fd(int *saved_in, int *saved_out);
void		dup_for_redirs(t_command *cmd_struct);
void		exec_external_command(t_data *data, char **cmd);
int			open_rdirin(char *filename);
char		**add_cmd(t_command *cmd_struct, t_token *tmp);
char		**fork_for_pipe(t_data *data, int num_cmds, t_pipe_fd fds);
void		init_cmd(t_command *cmd_struct);
void		mer_verjin_huys(t_command *cmd_struct);

// Libft functions
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dest, char *src);
void		add_back(t_token *node, t_token **a);
int			ft_atol(const char *str, long long *result);
int			ft_strcmp(char *s1, char *s2);
int			ft_strlen(const char *str);
int			length(int n);
int			in_set(char *s, char c);

// Tokenization functions
void		validation(char **line, t_token **stack, t_env **env);
void		init_tokens_type(t_token **stack);
void		check_type_pipe(char *str, t_token **stack);
void		check_type_red_in(char *str, t_token **stack);
void		check_type_red_out(char *str, t_token **stack);
void		check_type_heredoc(char *str, t_token **stack);
void		check_type_append(char *str, t_token **stack);
void		flush_word_before_op(t_val *val, char **line, t_env **env,
				t_token **stack);
void		flush_remainder(t_val *val, char **line, t_env **env,
				t_token **stack);
void		handle_operator(t_val *val, char **line, t_token **stack);
t_token		*if_cur_ind_equal_minus_one(t_val *val, char **line, t_env **env);
void		for_all_cases(t_val *val, char **line, t_env **env,
				t_token **stack);
int			get_operator_length(char *s);

// Built-in functions
void		exit_command(t_token **stack, t_env **env, char **split);
int			find_equal(char *str);
void		pwd_command(void);
void		env_command(t_env *env, t_token *stack);
void		*echo_command(t_token **stack);
void		*export_command(t_data *data, t_token *stack);
void		cd_command(t_token *stack, t_env **env);
void		update_env_new_and_old_pwd(t_env **env, char *old_pwd,
				char **target);
void		print_cd_error(char *target);
void		built_in_functions(t_data *data, t_token **stack, char *string);
void		unset_command(t_data *data);
int			is_builtin_cmd(char *cmd);

// Free functions
void		free_env(t_env **env);
void		free_array(char **array);
void		free_stack(t_token **stack);
void		free_all(t_env **env, t_token **stack, char **split);

// Env functions
void		add_env_value(t_env **env, char *key, char *value);
void		env_add_back(t_env *node, t_env **head);
void		change_shlvl_value(t_env **env, char **cmd);
char		*get_env_value(t_env *env, char *key);
t_env		*new_node(char *key, char *value);
t_env		*add_env_to_list(char **envp);
t_token		*create_node(char **res);
t_env		*copy_env_for_print(t_env *env);
char		**env_to_envp(t_env *env);

// Export functions
t_env		*sort_env(t_env *env);
int			find_plus(char *str);
int			check_key(char *key);
int			find_plus_equal(char *str);
int			find_equal_for_export(char *str);
int			check_sameness(char *str, t_env *env);
void		check_i_have_value_after_equal_symbol_version_two(int index,
				char *str, t_env **env);
void		check_i_have_value_after_equal_symbol(int index, char *str,
				t_env **node);
void		change_value_for_plus_equal_case(char *str, t_env **env);
void		change_value(char *str, t_env **env);
void		print_error_export(char *str);
void		print_export(t_env *env);

// Signal functions
void		handle_ctrl_d(void);
void		setup_signals(void);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		parent_process_handling(pid_t pid, int *status, char **cmd);
void		child_process_execution(t_env **env, char **cmd);
void		handle_wait_status(void);
void		wait_for_children(int num_cmds, int *exit_codes);

// Path functions
void		execve_case(char *cmd, char **path, char **envp);
int			is_directory(const char *path);
void		error_msg_dir(char *str);
void		dir_error(char **path, char **envp, char **cmd);

#endif
