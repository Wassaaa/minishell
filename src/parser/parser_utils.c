/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:06:04 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/16 23:58:18 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_quotes(char *value)
{
	while (*value)
	{
		if (is_quote(*value))
			return (1);
		value++;
	}
	return (0);
}

static int	contains_space(char *var)
{
	char	quote;

	quote = 0;
	while (*var)
	{
		if (!quote && is_whitespace(*var))
			return (1);
		if (!quote && is_quote(*var))
			quote = *var;
		else if (quote && *var == quote)
			quote = 0;
		var++;
	}
	return (0);
}

int	is_ambiguous(char *val, char *key)
{
	if (contains_space(val) || (val && !*val && key && *key == '$'))
	{
		print_error(ERR_MS, key, ERR_AMBIGUOUS, 0);
		ms()->exit = 1;
		return (1);
	}
	return (0);
}

static void	handle_quotes(char **val)
{
	char	quote;

	quote = **val;
	ft_memmove(*val, *val + 1, ft_strlen(*val));
	while (**val)
	{
		if (**val == quote)
		{
			ft_memmove(*val, *val + 1, ft_strlen(*val));
			break ;
		}
		(*val)++;
	}
}

char	*handle_node_quotes(char *val)
{
	char	*current;
	char	*new_val;
	size_t	len;

	len = ft_strlen(val);
	current = val;
	while (*current)
	{
		if (is_quote(*current))
			handle_quotes(&current);
		else
			current++;
	}
	if (ft_strlen(val) != len)
	{
		new_val = ft_safe_strdup(val);
		ft_free((void **)&val);
		return (new_val);
	}
	return (val);
}
