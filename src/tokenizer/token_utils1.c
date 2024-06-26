/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:46:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 13:39:34 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	while (*str && (is_word(*str)))
		str++;
	return (str);
}

char	*skip_op(char *str)
{
	if (is_double_operator(str))
		str += 2;
	else if (is_operator(*str))
		str++;
	return (str);
}

char	*skip_quote(char *str)
{
	char	*end;
	char	quote_type;

	quote_type = *str;
	str++;
	end = ft_strchr(str, quote_type);
	if (end == NULL)
		return (NULL);
	return (end + 1);
}
