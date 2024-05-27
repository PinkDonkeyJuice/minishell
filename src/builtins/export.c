/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:46:31 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/27 13:14:21 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_data *data)
{
	t_env	*print;
	size_t	i;

	i = 0;
	print = data->env_c;
	while (print)
	{
		ft_putstr_fd("declare -x ", 1);
		while (print->content[i])
		{
			ft_putchar_fd(print->content[i], 1);
			if (print->content[i] == '=')
				ft_putchar_fd('"', 1);
			i++;
		}
		ft_putstr_fd("'"'\n", 2);
		print = print->next;
	}
}

void	replace_var(t_env *to_replace, char *var_def)
{
	free(to_replace->content);
	to_replace->content = ft_strdup(var_def);
}

int	is_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] != '=')
			return (1);
		if (((var[i] >= '0' && var[i] <= '9') || var[i] == '=') && i == 0)
			return (0);
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	export_var(t_env **to_replace, char **var_def, t_data *data)
{
	*to_replace = search_var(*var_def, data);
	if (*to_replace != NULL)
		replace_var(*to_replace, *var_def);
	else
		append_node(&(data->env_c), *var_def);
}

void	exec_export(t_data *data)
{
	int		i;
	char	*var_def;
	t_env	*to_replace;	

	i = 1;
	if (data->commands == NULL || data->commands[0] == NULL)
		return ;
	if (!data->commands[1])
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
