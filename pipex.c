/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:38:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/19 16:45:42 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_process(char **argv, char **envp, t_pipex *px)
{
	pid_t	p[2];

	if (pipe(px->p_fd) < 0)
		error_exit("pipe func error");
	p[0] = fork();
	if (p[0] < 0)
		error_exit("fork1 func error");
	else if (p[0] == 0)
	{
		fork_process(argv[2], envp, px, 0);
	}
	p[1] = fork();
	if (p[1] < 0)
		error_exit("fork2 func error");
	else if (p[1] == 0)
	{
		fork_process(argv[3], envp, px, 1);
	}
	close_px(px);
	wait(NULL);
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc != 5)
	{
		ft_putendl_fd("Error\nMust have 4 arguments", 2);
		exit(1);
	}
	ft_memset(&px, 0, sizeof(t_pipex));
	open_files(argv[1], argv[4], &px);
	pipex_process(argv, envp, &px);
	return (0);
}
