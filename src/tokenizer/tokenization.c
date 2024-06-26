/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:41:14 by aklein            #+#    #+#             */
/*   Updated: 2024/06/10 10:12:31 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_token_to_list(t_token_list **lst, t_token_list *node)
{
	t_token_list	*last;

	if (*lst == NULL)
		*lst = node;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = node;
		last->next->prev = last;
	}
}

static t_token_list	*create_token(t_token_type type, char *value)
{
	t_token_list	*node;

	node = ft_safe_calloc(1, sizeof(t_token_list));
	if (type == WORD)
		node->expand = 1;
	node->type = type;
	node->value = value;
	return (node);
}

t_token_list	*new_tokenizer(char *str, int ops)
{
	t_token_list	*lst;
	t_token_list	*node;
	char			*value;
	t_token_type	type;

	lst = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break ;
		extract_token(str, &value, &type);
		if (!ops)
			type = WORD;
		node = create_token(type, value);
		add_token_to_list(&lst, node);
		str += token_len(str);
	}
	return (lst);
}
