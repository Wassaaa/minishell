/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/14 00:51:54 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parent(t_list *cmds, int *pipe_in)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmds->content;
	safe_close(*pipe_in);
	if (cmds->next != NULL)
	{
		safe_close(ms()->pipefd[P_WRITE]);
		*pipe_in = safe_dup(ms()->pipefd[P_READ]);
		safe_close(ms()->pipefd[P_READ]);
	}
	safe_close(cmd->in_file.fd);
	safe_close(cmd->out_file.fd);
}

static int	get_status(int status)
{
	if (WIFSIGNALED(status) != 0)
		return (E_CODE_SIG + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static void	wait_for_children(void)
{
	int	i;
	int	status;

	i = 0;
	while (i < ms()->cmds_num)
	{
		waitpid(ms()->pids[i], &status, 0);
		ms()->exit = get_status(status);
		i++;
	}
}

void	execute_commands(t_list *cmds)
{
	int		pipe_in;
	int		i;

	i = 0;
	pipe_in = -1;
	ms()->pids = ft_safe_calloc(ms()->cmds_num, sizeof(pid_t));
	if (ms()->cmds_num == 1 && cmds && is_special_builtin(cmds->content))
	{
		execute_builtin(cmds->content);
		return ;
	}
	while (cmds)
	{
		if (cmds->next != NULL)
			safe_pipe(ms()->pipefd);
		set_signals(SIG_FORK);
		ms()->pids[i] = safe_fork();
		if (ms()->pids[i] == 0)
			child(cmds, &pipe_in);
		if (ms()->pids[i++] > 0)
			parent(cmds, &pipe_in);
		cmds = cmds->next;
	}
	wait_for_children();
}
