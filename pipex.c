/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:38:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/23 17:56:55 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_process(char **argv, char **envp, t_pipex *px)
{
	pid_t	p[2];

	if (pipe(px->p_fd) < 0)
		error_exit("pipe func error", px);
	p[0] = fork();
	if (p[0] < 0)
		error_exit("fork1 func error", px);
	else if (p[0] == 0)
	{
		fork_process(argv[2], envp, px, 0);
	}
	p[1] = fork();
	if (p[1] < 0)
		error_exit("fork2 func error", px);
	else if (p[1] == 0)
	{
		fork_process(argv[3], envp, px, 1);
	}
	fds_handle(px, 1);
	wait(NULL);
	wait(NULL);
}

void	command_validation(char *cmd, char **envp, t_pipex *px)
{
	char	**args;
	char	*val;

	args = ft_split(cmd, ' ');
	if (!args)
		error_exit("split error", px);
	if (!ft_strchr(args[0], '/'))
	{
		val = cmd_path(envp, args);
		free_array(args);
		if (!val)
			error_exit("invalid command", px);
		free(val);
	}
	else
	{
		if (access(args[0], X_OK) < 0)
		{
			free_array(args);
			error_exit("invalid command", px);
		}
		free_array(args);
	}
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
	fds_handle(&px, 0);
	command_validation(argv[2], envp, &px);
	command_validation(argv[3], envp, &px);
	open_files(argv[1], argv[4], &px);
	pipex_process(argv, envp, &px);
	return (0);
}
