/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:46:31 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/04 11:53:51 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_data *data)
{
	t_env	*print;
	size_t	i;

	print = data->env_c;
	while (print)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (print->content[i])
		{
			ft_putchar_fd(print->content[i], 1);
			if (print->content[i] == '=')
				ft_putchar_fd('"', 1);
			i++;
		}
		if (search_equal(print->content) == 1)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		print = print->next;
	}
}

void	replace_var(t_env *to_replace, char *var_def)
{
	if (search_equal(var_def) == 0 && search_equal(to_replace->content) == 1)
		return ;
	free(to_replace->content);
	to_replace->content = ft_strdup(var_def);
}

int	is_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (((var[i] >= '0' && var[i] <= '9') || var[i] == '=') && i == 0)
			return (0);
		if (var[i] == '=' && i != 0)
			return (1);
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	export_var(t_env **to_replace, char **var_def, t_data *data)
{
	*to_replace = search_var(*var_def, data);
	if (*to_replace != NULL && (*to_replace)->modifiable == false)
		return ;
	if (*to_replace != NULL)
		replace_var(*to_replace, *var_def);
	else
		append_node(&(data->env_c), *var_def);
}

void	exec_export(t_data *data, bool is_main)
{
	int		i;
	char	*var_def;
	t_env	*to_replace;	

	i = 1;
	if (data->commands == NULL || data->commands[0] == NULL)
		return ;
	if (!data->commands[1] && ((!is_main && data->n_commands > 1)
			|| (is_main && data->n_commands == 1)))
		return (print_export(data));
	var_def = data->commands[i];
	while (var_def != NULL && data->n_commands == 1)
	{
		if (!is_valid(data->commands[i]))
			printf("minishell: export: '%s': not a valid identifier\n",
				data->commands[i]);
		else
			export_var(&to_replace, &var_def, data);
		i++;
		var_def = data->commands[i];
	}
}
