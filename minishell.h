/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/07/21 12:15:30 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_stack
{
	char			*string;
	struct s_stack	*next;
}	t_stack;

typedef struct s_info
{
	int	single_quotes;
	int	double_quotes;
	int	back_quotes;
}	t_info;

t_stack	*create_node(char *res);
char	**ft_split(char const *s);
void	add_back(t_stack *node, t_stack **a);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
char	*ft_strstr(char *str, char *to_find);
# endif

