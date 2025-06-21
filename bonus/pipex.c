/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:09 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/19 17:57:04 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void here_doc_pipex()
{
	printf("here_doc\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		cmd;

	ft_memset(&px, 0, sizeof(t_pipex));
	px.argc = argc;
	if (!ft_strncmp("here_doc", argv[1], 8))
		here_doc_pipex();
	else
	{
		open_files(argv[1], argv[argc - 1], &px);
		cmd = 2;
		while(cmd <= px.argc - 2)
			pipex_process(argv, envp, &px, cmd++);
	}
	return (0);
}
