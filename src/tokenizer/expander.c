/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/18 18:01:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	process_var_assigment(char **input, t_var_list *v)
{
	char	*equal_pos;
	char	*expanded;
	char	*prefix;
	char 	*new_input;
	char	*unquoted;
	
	// assign a variable with an empty string
	// var is created, value = empty string
	if (*input == NULL || **input == '\0')
	{
		add_var(&v, *input);
		return ;
	}
	new_input = NULL;
	equal_pos = ft_strchr(*input, '=');
	if (equal_pos)
	{
		prefix = ft_strndup(*input, (equal_pos + 1) - *input);
		unquoted = remove_outer_quotes(equal_pos + 1);
		//ARG=$USER-> ARG=lumik
		if (is_double_quoted(equal_pos + 1) && ft_strchr(unquoted, '$'))
		{
			expanded = expand_variable(unquoted, v);
			new_input = ft_strjoin(prefix, expanded);
			//printf("expanded_var_input: %s\n", new_input);
			free(prefix);
			if (new_input)
				*input = new_input;
		}
		else
		{
			free(*input); // If the token is not quoted at all, free the original value
			*input = unquoted;
		}
		if (new_input)
            add_var(&v, new_input);
        else
            add_var(&v, *input);
    }
	else // ARG=value or ARG=" la hello"
		add_var(&v, *input);
}

static char *lookup_var(char *var_name, t_var_list *v)
{
	while (v)
	{
		if (ft_strcmp(v->current_var->name, var_name) == 0)
			return (ft_strdup(v->current_var->value));
		v = v->next;
	}
	return (NULL);
}

char	*expand_variable(char *str, t_var_list *v)
{
	char	*start;
	char	*prefix;
	char	*end;
	char 	*expanded_str;
	char	*temp;
	char	*var_name;
	char	*var_value;

	start = ft_strchr(str, '$');
	end = skip_variable(start);
	prefix = ft_strndup(str, start - str);
	var_name = ft_strndup(start + 1, end - start - 1);
	var_value = lookup_var(var_name, v);
	if (var_value)
	{
		temp = ft_strjoin(prefix, var_value);
		expanded_str = ft_strjoin(temp, end);
		free(temp);
	}
	else	
		expanded_str = ft_strdup(str);
	free(prefix);
	return (expanded_str);
}
