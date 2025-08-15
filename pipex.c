/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:09 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/14 16:42:42 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp) //fracionar funçoes
{
	t_pipex	px;
	int		cmd;

	ft_memset(&px, 0, sizeof(t_pipex));
	fds_handle(&px, 0);
	px.argc = argc;
	if (!ft_strncmp("here_doc", argv[1], 8))
		here_doc_fill(argv, &px);
	else 
	{
		if (px.argc < 5)
		{
			ft_putendl_fd("4 arguments minimum", 2);
			exit(1);
		}
		px.first_cmd = 2;
	}
	cmd = px.first_cmd;
	while (cmd <= px.argc - 2)
	{
		px.args = px_split(argv[cmd]);
		px.path = cmd_path(envp, &px);
		pipex_process(envp, &px, cmd++, argv);
		free(px.path);
		free_array(px.args);
	}
	waitpid(px.pid, &px.exit_status, 0);
	px.processes--;
	while (px.processes--)
		wait(NULL);
	if (WIFEXITED(px.exit_status))
		return WEXITSTATUS(px.exit_status);
	else if (WIFSIGNALED(px.exit_status))
		return 128 + WTERMSIG(px.exit_status);
	else
		return 1;
}
