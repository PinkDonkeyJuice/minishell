/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:34:45 by nchaize-          #+#    #+#             */
/*   Updated: 2024/04/16 12:13:14 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_last_node(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	append_node(t_env **env, char *env_var)
{
	t_env	*node;
	t_env	*last_node;

	if (!env)
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->next = NULL;
	node->data = env_var;
	if (*env == NULL)
		*env = node;
	else
	{
		last_node = find_last_node(*env);
		last_node->next = node;
	}
}

void	init_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	data->env = NULL;
	while (env[i])
	{
		append_node(&(data->env), env[i]);
		i++;
	}
}
