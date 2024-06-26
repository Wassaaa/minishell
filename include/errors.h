/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:50:18 by aklein            #+#    #+#             */
/*   Updated: 2024/06/17 00:50:54 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ALLOC "Allocation error."
# define ERR_MS "minishell"
# define ERR_QUOTES "syntax error, quotes not matched"
# define ERR_PIPES "syntax error, pipe all alone in the end"
# define ERR_NEAR_TOKEN "syntax error near unexpected token `"
# define ERR_KEY_VALID "not a valid identifier"
# define ERR_AMBIGUOUS "ambiguous redirect"
# define ERR_CD_ARGS "too many arguments"
# define ERR_CD_HOME "HOME not set"
# define NL	"newline"
# define ERR_PIPE "pipe failed"
# define ERR_DUP2 "dup2 failed"
# define ERR_FORK "fork failed"
# define ERR_EXECVE "execve failed"
# define ERR_WAITPID "waitpid failed"
# define ERR_FILE "No such file or directory"
# define ERR_CMD "command not found"
# define ERR_DIR "Is a directory"
# define ERR_PERM "Permission denied"
# define HD_EOF1 "here-document at line "
# define HD_EOF2 " delimited by end-of-file (wanted `"
# define HD_EOF3 "')"
# define ERR_CD1 "cd: error retrieving current directory"
# define ERR_CD2 "cannot access parent directories"
# define ERR_FORK_QUIT "Quit (core dumped)\n"

# define E_CODE_CMD_NEXEC 126
# define E_CODE_CMD_NFOUND 127
# define E_CODE_SIG 128
# define E_CODE_SYNTX 2
# define E_CODE_FILE 1
#endif