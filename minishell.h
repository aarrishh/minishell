/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 18:38:18 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <limits.h>

# define ANSI(code) "\001" code "\002"
# define P ANSI("\033[38;2;255;204;213m")		// pink
# define PB ANSI("\033[1;38;2;255;204;213m")	// bold pink
# define W ANSI("\033[38;2;255;255;255m")		// white
# define R ANSI("\033[0m")						// reset

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	WORD,      // 0
	PIPE,      // | 1
	REDIR_IN,  // < 2
	REDIR_OUT, // > 3
	HEREDOC,   // << 4
	APPEND,    // >> 5
	LIM        // 6
}	t_token_type;

typedef struct s_cmd
{
	char			*command;
	char			*infile;
	char			*outfile;
	char			*delimiter;  // for heredoc
	int				append;      // 0 for >, 1 for >>
	int				heredoc;     // 1 if <<
	int				is_builtin;  // 1 if yes, 0 no
	struct s_cmd	*next;       // for pipeline
}	t_cmd;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_quote_state
{
	NO_QUOTE,
	IN_SINGLE,
	IN_DOUBLE,
}	t_quote_state;

// Libft functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strstr(char *str, char *to_find);
void	add_back(t_token *node, t_token **a);
int		ft_atol(const char *str, long long *result);
int 	ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);

// Tokenization functions
void	validation(char **line, t_token **stack);
void	init_tokens_type(t_token **stack);

// Quote functions
int		len_without_quote(char *line, t_quote_state state);
int		urish_len(char *line);
char	*expand_quotes(char *line);
char	*cut_quotes(char *line, t_quote_state state);
char	*open_dquote(t_quote_state state, char *line);
void	start_quotes(char *line, char ***split);

// Built-in functions
int		exit_command(t_token **stack);
int		find_equal(char *str);
void	pwd_command(void);
void	env_command(t_env *env);
void	*echo_command(t_token **stack);
void	export_command(t_token *stack, t_env **env);
void	cd_command(t_token *stack, t_env **env);
void	built_in_functions(t_token **stack, t_env **env);

// Env functions
void	env_add_back(t_env *node, t_env **head);
t_env	*new_node(char *key, char *value);
t_env	*add_env_to_list(char **envp);
t_token	*create_node(char *res);

// Export functions
t_env	*sort_env(t_env *env);
int		find_plus(char *str);
int		check_key(char *key);
int		find_plus_equal(char *str);
int		find_equal_for_export(char *str);
int		check_sameness(char *str, t_env *env);
void	check_i_have_value_after_equal_symbol_version_two(int index, char *str, t_env **env);
void	check_i_have_value_after_equal_symbol(int index, char *str, t_env **node);
void	change_value_for_plus_equal_case(char *str, t_env **env);
void	change_value(char *str, t_env **env);
void	print_error_export(char *str);
void	print_export(t_env *env);

#endif
