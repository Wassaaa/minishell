/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:42 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 13:59:34 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

/*static int	len_inquote(char *str)
{
	char *end;
	int len;

	len = 0;
	str++;
	end = str;
	end = skip_quote(str);
	end--;
	len = end - str;
	return (len);
}
// find the end of token OP_ and WORD
static char	*find_token_end(char *str)
{
	char	*end;

	end = str;
	if (is_operator(*str))
		end++;
	else
		while (*end && !is_whitespace(*end) 
			&& !is_operator(*end) && *end != '$')
			end++;
	return (end);
}

int	get_token_len(char *str)
{
	int		len;
	char	*end;
	
	if (is_quote(*str))
	{
		len = len_inquote(str);
		str++;
	}
	else if (is_double_operator(str))
		len = 2;
	else if (*str == '$')
	{
		end = find_var_end(str);
		len = end - str;
	}
	else
	{
		end = find_token_end(str);
		len = end - str;
	}
	return (len);
}*/

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

t_token_type	get_token_type(char *str)
{
	if (*str == '\'')
		return (S_QUOTE);
	else if (*str == '\"')
		return (D_QUOTE);
	else if (ft_strcmp(str, "<<") == 0)
		return (OP_DLESS);
	else if (ft_strcmp(str, ">>") == 0)
		return (OP_DGREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '|')
		return (OP_PIPE);
	else if (str[0] == '$')
		return (VAR);
	else
		return (WORD);
}

static const char	*get_type_str(int e)
{
	static const char	*type_str[] = {
		"WORD",
		"OP_PIPE",
		"OP_LESS",
		"OP_GREAT",
		"OP_DLESS",
		"OP_DGREAT",
		"S_QUOTE",
		"D_QUOTE",
		"VAR",
		"T_NEWLINE",
		"T_SPACE",
		"UNKNOWN"
	};

	return (type_str[e]);
}

void	print_type(int e, const char *str)
{
	const char	*message;

	if (e >= 0 || e < UNKNOWN)
	{
		message = get_type_str(e);
		ft_putstr_fd(message, STDERR_FILENO);
	}
	write(2, "\n", 1);
}

char	*ft_strndup(char *str, size_t len)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}