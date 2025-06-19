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
//reformular o loop e rechamar pipe() quando for a reutilizacao erro tambem na passado de argumento
//tirar o while e chamar manualmento o numero correto de funcoes
//para cada pipe existe 1 chamada de pipe() e duas de fork()
int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		pipe_op;

	ft_memset(&px, 0, sizeof(t_pipex));
	px.argc = argc;
	if (!ft_strncmp("here_doc", argv[1], 8))
		here_doc_pipex();
	else
	{
		if (pipe(px.p1_fd) < 0)
			error_exit("pipe1 func error");
		if (pipe(px.p2_fd) < 0)
			error_exit("pipe2 func error");
		open_files(argv[1], argv[argc - 1], &px);
		pipe_op = 1;
		while(pipe_op <= px.argc - 2)
			pipex_process(argv, envp, &px, pipe_op++);//deve executar um comportamento de pipe completo nao um fork apenas
	}
	return (0);
}
