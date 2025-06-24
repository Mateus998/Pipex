/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:09 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/24 17:27:41 by mateferr         ###   ########.fr       */
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
	{
		px.file_fd[0] = open(argv[1], O_RDONLY);
		if (px.file_fd[0] == -1)
			perror(argv[1]);
		px.first_cmd = 2;
	}
	cmd = px.first_cmd;
	while (cmd <= px.argc - 2)
	{
		if (cmd == px.argc - 2)
			open_outfile(&px, argv[argc - 1]);
		pipex_process(argv, envp, &px, cmd++);
	}
	return (0);
}
