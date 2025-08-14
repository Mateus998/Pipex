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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		cmd;

	ft_memset(&px, 0, sizeof(t_pipex));
	fds_handle(&px, 0);
	px.argc = argc;
	if (!ft_strncmp("here_doc", argv[1], 8))
		here_doc_fill(argv, &px);
	else
		file_read(&px, argv[1], argv[argc - 1]);
	cmd = px.first_cmd;
	while (cmd <= px.argc - 2)
	{
		px.args = px_split(argv[cmd]);
		px.path = cmd_path(envp, &px);
		pipex_process(envp, &px, cmd++);
		free(px.path);
		free_array(px.args);
	}
	waitpid(px.pid, NULL, 0);
	px.processes--;
	while (px.processes--)
		wait(NULL);
	return (0);
}
