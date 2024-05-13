/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:15:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 23:00:29 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_double_operator(char *str)
{
	return ((*str == '>' && *(str + 1) == '>')
		|| (*str == '<' && *(str + 1) == '<'));
}

char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}