/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:26:30 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/02 22:20:34 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
}					t_env;

typedef enum e_quote_state
{
	NO_QUOTE,
	IN_SINGLE,
	IN_DOUBLE,
}					t_quote_state;

typedef struct s_iter
{
	int				i;
	int				j;
}					t_iter;

typedef enum e_token_type
{
	WORD,      // 0
	PIPE,      // | 1
	REDIR_IN,  // < 2
	REDIR_OUT, // > 3
	APPEND,    // >> 5
	HEREDOC,   // << 4
}					t_token_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	t_token			*stack;
	t_env			*env;
	char			**envp;
	char			**split;
}					t_data;

char				**split_for_quotes(char const *s, char c);
void				handle_dollar(char *line, char *new, t_iter *ij,
						t_env **env);
void				keep_char(char *line, char *new, t_iter *ij);
int					key_len(char *str);
t_quote_state		quote_state(t_quote_state state, char c);
int					is_quote_closed(char *line);
void				keep_value(char *new, char *value, int *j);
void				exp_help_loop(t_quote_state state, char *str, char *new,
						t_iter *ij, t_env **env);
char				*find_var_value(char *str, t_env **env, int *key_len);
t_quote_state		handle_double_quote_len(char *line, int *i, int *len,
						t_env **env);
int					len_without_quote(char *line, t_quote_state state);
void				handle_len_dollar(char *line, int *i, int *len,
						t_env **env);
t_quote_state		handle_single_quote_len(char *line, int *i, int *len);
int					len_for_malloc(char *line, t_env **env);
void				loop(char *line, char *new, t_quote_state state,
						t_env **env_struct);
char				*expand_quotes(char *line, t_env **env_struct);
int					start_quotes(char *line, t_data *data);
char				*open_dquote(t_quote_state state, char *line);
char				*cut_quotes(char *line, t_quote_state state);

#endif