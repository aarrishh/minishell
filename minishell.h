/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/08/09 17:42:04 by mabaghda         ###   ########.fr       */
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

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_token				*create_node(char *res);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strstr(char *str, char *to_find);
void				add_back(t_token *node, t_token **a);
void				validation(char **line, t_token **stack);
void				init_tokens_type(t_token **stack);
int					ft_strcmp(char *s1, char *s2);
int					ft_strlen(const char *str);
void				built_in_functions(t_token **stack, t_env **env);
int					ft_atol(const char *str, long long *result);
t_env				*add_env_to_list(char **envp);
void				execute_pipe(t_token **stack, t_env **env, char **envp);
char				**split_pipe(t_token **stack);
void				execute_else(t_token **stack, t_env **env, char *cmd,
						char **envp);
int					is_builtin(t_token *stack);
char				*split_path(t_env **env, char *cmd);

#endif
