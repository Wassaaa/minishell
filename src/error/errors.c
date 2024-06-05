/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:25:06 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 13:09:51 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(int exit_code)
{
	perror(ERR_MS);
	ms_exit(FATAL, exit_code);
}



void	print_error(char *from, char *bad_arg, char *custom, int is_errno)
{
	if (from)
	{
		ft_putstr_fd(from, 2);
		ft_putstr_fd(": ", 2);
	}
	if (is_errno)
	{
		if (bad_arg)
			perror(bad_arg);
		else
			perror(NULL);
	}
	else
	{
		if (bad_arg)
		{
			ft_putstr_fd(bad_arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(custom, 2);
	}
}

int	quote_match_check(char *input)
{
	char	quote_type;

	quote_type = 0;
	while (*input)
	{
		if (!quote_type && is_quote(*input))
			quote_type = *input;
		else if (*input == quote_type)
			quote_type = 0;
		input++;
	}
	if (quote_type == 0)
		return (1);
	print_error(ERR_MS, NULL, ERR_QUOTES, 0);
	return (0);
}

int	pipe_start_end(t_token_list *tokens)
{
	if (tokens->type == OP_PIPE)
		return (0);
	while (tokens)
		tokens = tokens->next;
	if (tokens->type == OP_PIPE)
		return (0);
	return (1);
}

void	print_near_error(t_token_list *near)
{
	char	*token_val;
	char	*start;
	char	*final;

	if (!near)
		token_val = NL;
	else
		token_val = near->value;
	start = ft_safe_strjoin(ERR_NEAR_TOKEN, token_val);
	final = ft_safe_strjoin(start, "\'");
	ft_free((void **)&start);
	print_error(ERR_MS, NULL, final, 0);
	ft_free((void **)&final);
}

int	check_op_syntax(t_token_list *token)
{
	t_token_type	current;

	current = token->type;
	if (!token->next)
		return (0);
	if (current == OP_PIPE)
		if (token->next->type == OP_PIPE)
			return (0);
	if (current >= OP_LESS && current <= OP_DGREAT)
		if (token->next->type != WORD)
			return (0);
	return (1);
}

int	near_token_errors(t_token_list *tokens)
{
	t_token_list	*near;

	if (!tokens)
		return (0);
	if (tokens->type == OP_PIPE)
	{
		print_near_error(tokens);
		return (0);
	}
	while (tokens)
	{
		near = tokens->next;
		if (tokens->type != WORD)
		{
			if (!check_op_syntax(tokens))
			{
				print_near_error(near);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
