/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:38:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/17 15:31:35 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_print(t_pipex *pipex)
{
	int	i;

	i = 0;
	ft_printf("fd1\n%i\n", pipex->fd[0]);
	ft_printf("\ncmd1\n");
	while (pipex->cmd1[i])
		ft_printf("%s ", pipex->cmd1[i++]);
	ft_printf("\n\ncmdpath1\n%s\n", pipex->cmdpath1);
	ft_printf("\nfd2\n%i\n", pipex->fd[1]);
	i = 0;
	ft_printf("\ncmd2\n");
	while (pipex->cmd2[i])
		ft_printf("%s ", pipex->cmd2[i++]);
	ft_printf("\n\ncmdpath2\n%s\n", pipex->cmdpath2);
	i = 0;
	ft_printf("\npath\n");
	while (pipex->path[i])
		ft_printf("%s\n", pipex->path[i++]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		error_exit("Must have 4 arguments");
	pipex = input_validation(argv, envp);
	pipe_process(pipex);
	pipex_print(pipex);
	free_pipex(pipex);
	return (0);
}
