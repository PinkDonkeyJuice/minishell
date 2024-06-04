/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:34:45 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/04 15:47:37 by nchaize-         ###   ########.fr       */
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
	node->previous = NULL;
	node->content = ft_strdup(env_var);
	if (node->content == NULL)
		return ;
	if (*env == NULL)
		*env = node;
	else
	{
		last_node = find_last_node(*env);
		last_node->next = node;
		node->previous = last_node;
	}
	node->modifiable = true;
	if (env_var && env_var[0] == '_')
		node->modifiable = false;
}

void	fill_basic_env(t_data *data)
{
	char	buf[PATH_MAX];
	char	*result;
	char	*temp;

	getcwd(buf, PATH_MAX);
	result = ft_strjoin("PWD=", buf);
	if (!result)
		return ;
	append_node(&(data->env_c), result);
	free(result);
	append_node(&(data->env_c), "SHLVL=1");
	temp = ft_strjoin(buf, "/./minishell");
	if (!temp)
		return ;
	result = ft_strjoin("_=", temp);
	if (!result)
	{
		free(temp);
		return ;
	}
	append_node(&(data->env_c), result);
	free(temp);
	free(result);
}

void	init_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	data->env_c = NULL;
	if (env[i] == NULL)
		fill_basic_env(data);
	while (env[i])
	{
		append_node(&(data->env_c), env[i]);
		i++;
	}
}
