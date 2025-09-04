/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 07:00:52 by arina             #+#    #+#             */
/*   Updated: 2025/09/04 19:22:53 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_list_remove_if(t_env **begin_list, char *data_ref, int (*cmp)())
{
	t_env	*cur;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	if (cmp(cur->key, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_list_remove_if(&(cur->next), data_ref, cmp);
}

void	find_key_for_unset(char *str, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
		{
			ft_list_remove_if(env, str, ft_strcmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	unset_command(t_data *data)
{
	t_token	*tmp;

	tmp = data->stack;
	if (!tmp->next)
		return ;
	tmp = tmp->next;
	while (tmp)
	{
		if (check_key(tmp->string) == -2)
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				tmp->string);
			g_exit_status = 1;
			return ;
		}
		find_key_for_unset(tmp->string, &data->env);
		tmp = tmp->next;
	}
	g_exit_status = 0;
	update_envp(data);
}
