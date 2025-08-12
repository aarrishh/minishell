/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/08/11 18:06:12 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "quotes/quotes.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PB "\001\033[1;38;2;255;204;213m\002" // bold pink
# define W "\001\033[38;2;255;255;255m\002"    // white
# define R "\001\033[0m\002"                   // reset

typedef enum e_token_type
{
	WORD,      // 0
	PIPE,      // | 1
	REDIR_IN,  // < 2
	REDIR_OUT, // > 3
	HEREDOC,   // << 4
	APPEND,    // >> 5
	LIM        // 6
}					t_token_type;

typedef struct s_minishell {
	int exit_status;
}	t_minishell;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

// Pipe functions
void				execute_pipe(t_token **stack, t_env **env, char **envp, char **split);
char				**split_pipe(t_token **stack);
void				execute_else(t_env **env, char **cmd, char **envp);
char				*split_path(t_env **env, char *cmd);
int					has_pipe(t_token *stack);

// Libft functions
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strstr(char *str, char *to_find);
void				add_back(t_token *node, t_token **a);
int					ft_atol(const char *str, long long *result);
int					ft_strcmp(char *s1, char *s2);
int					ft_strlen(const char *str);

// Tokenization functions
void				validation(char **line, t_token **stack);
void				init_tokens_type(t_token **stack);
void				check_type_pipe(char *str, t_token **stack);
void				check_type_red_in(char *str, t_token **stack);
void				check_type_red_out(char *str, t_token **stack);
void				check_type_heredoc(char *str, t_token **stack);
void				check_type_append(char *str, t_token **stack);

// Built-in functions
int					exit_command(t_token **stack, t_env **env, char **split);
int					find_equal(char *str);
void				pwd_command(void);
void				env_command(t_env *env);
void				*echo_command(t_token **stack);
void				export_command(t_token *stack, t_env **env);
void				cd_command(t_token *stack, t_env **env);
void				built_in_functions(t_token **stack, char *string, t_env **env, char **split);
void				unset_command(t_token *stack, t_env **env);
int					is_builtin_cmd(char *cmd);

// Free functions
void				free_stack(t_token **stack);
void				*free_array(char **array);
void				free_env(t_env **env);

// Env functions
void				env_add_back(t_env *node, t_env **head);
t_env				*new_node(char *key, char *value);
t_env				*add_env_to_list(char **envp);
t_token				*create_node(char *res);
	
// Export functions
t_env				*sort_env(t_env *env);
int					find_plus(char *str);
int					check_key(char *key);
int					find_plus_equal(char *str);
int					find_equal_for_export(char *str);
int					check_sameness(char *str, t_env *env);
void				check_i_have_value_after_equal_symbol_version_two(int index,
						char *str, t_env **env);
void				check_i_have_value_after_equal_symbol(int index, char *str,
						t_env **node);
void				change_value_for_plus_equal_case(char *str, t_env **env);
void				change_value(char *str, t_env **env);
void				print_error_export(char *str);
void				print_export(t_env *env);

#endif
