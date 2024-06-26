/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:04:56 by aklein            #+#    #+#             */
/*   Updated: 2024/06/13 04:59:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_token_quotes(t_token_list *tokens)
{
	char	*val;

	while (tokens)
	{
		val = tokens->value;
		tokens->value = handle_node_quotes(val);
		tokens = tokens->next;
	}
}

t_list	*parser(t_token_list *tokens)
{
	t_cmd	*new_cmd;
	t_list	*cmd_list;

	cmd_list = NULL;
	while (tokens)
	{
		new_cmd = simple_cmd(&tokens);
		ms()->exit = EXIT_SUCCESS;
		if (ms()->interrupt)
		{
			ms()->exit = E_CODE_SIG + SIGINT;
			return (NULL);
		}
		if (!validate_redir_list(new_cmd))
		{
			ms()->exit = EXIT_FAILURE;
			ft_free((void **)&new_cmd->command);
		}
		ft_lstadd_back(&cmd_list, ft_safe_lstnew(new_cmd));
		if (tokens)
			tokens = tokens->next;
	}
	ms()->cmds_num = ft_lstsize(cmd_list);
	return (cmd_list);
}
