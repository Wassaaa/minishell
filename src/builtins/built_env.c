/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:10 by aklein            #+#    #+#             */
/*   Updated: 2024/06/05 01:27:18 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_env(t_cmd *cmds)
{
	t_var_list	*envs;

	(void)cmds;
	envs = ms()->var_list;
	while (envs)
	{
		if (envs->key && envs->value)
			ft_printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
	ms()->exit = 0;
}
