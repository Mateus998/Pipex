/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:09 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/18 10:17:22 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	arg_count_here_doc_fill(char **argv, t_pipex *px)
{
	if (!ft_strncmp("here_doc", argv[1], 8))
		here_doc_fill(argv, px);
	else
	{
		if (px->argc < 5)
		{
			ft_putendl_fd("4 arguments minimum", 2);
			exit(1);
		}
		px->first_cmd = 2;
	}
}

static void	parent_processes_loop(t_pipex *px, char **argv, char **envp)
{
	int	cmd;

	cmd = px->first_cmd;
	while (cmd <= px->argc - 2)
	{
		px->args = px_split(argv[cmd]);
		px->path = cmd_path(envp, px);
		pipex_process(envp, px, cmd++, argv);
		free(px->path);
		free_array(px->args);
	}
	waitpid(px->pid, &px->exit_status, 0);
	px->processes--;
	while (px->processes--)
		wait(NULL);
}

static int	exit_status_return(t_pipex *px)
{
	if (WIFEXITED(px->exit_status))
		return (WEXITSTATUS(px->exit_status));
	else if (WIFSIGNALED(px->exit_status))
		return (128 + WTERMSIG(px->exit_status));
	else
		return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	ft_memset(&px, 0, sizeof(t_pipex));
	fds_handle(&px, 0);
	px.argc = argc;
	arg_count_here_doc_fill(argv, &px);
	parent_processes_loop(&px, argv, envp);
	return (exit_status_return(&px));
}
