/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/19 17:24:45 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	middle_dup_fds(int proc, t_pipex *px)
{
	if (proc % 2 == 0)
	{
		if (dup2(px->p1_fd[0], STDIN_FILENO) < 0)
			error_exit("mid read p1_fd dup error");
		if (dup2(px->p2_fd[1], STDOUT_FILENO) < 0)
			error_exit("mid read p2_fd dup error");
	}
	else
	{
		if (dup2(px->p2_fd[0], STDIN_FILENO) < 0)
			error_exit("mid read p2_fd dup error");
		if (dup2(px->p1_fd[1], STDOUT_FILENO) < 0)
			error_exit("mid write p1_fd dup error");
	}
}

void	middle_process(char *cmd, char **envp, t_pipex *px, int proc)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		error_exit("mid exec args error");
	path = cmd_path(envp, args);
	if (!path)
		error_exit("mid exec path error");
	middle_dup_fds(proc, px);
	close_px(px);
	execve(path, args, envp);
	free(path);
	free_array(args);
}

void	pipex_process(char **argv, char **envp, t_pipex *px, int proc)
{
	pid_t	p;

	p = fork();
	if (proc == 1)
	{
		if (p < 0)
			error_exit("begin fork error");
		else if (p == 0)
			fork_process(argv[2], envp, px, 0);
	}
	else if (proc == px->argc - 4)
	{
		if (p < 0)
			error_exit("end fork error");
		else if (p == 0)
			fork_process(argv[px->argc - 1], envp, px, proc);
	}
	else
	{
		if (p < 0)
			error_exit("middles fork error");
		else if (p == 0)
			middle_process(argv[proc + 1], envp, px, proc);
	}
	close_px(px);
	wait(NULL);
}
