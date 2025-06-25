/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/25 20:04:35 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	create_pipe(t_pipex *px, int cmd)
{
	int	*temp;

	if (cmd == px->first_cmd)
	{
		px->corr = px->p1_fd;
		px->prev = px->file_fd;
	}
	else if (cmd == px->argc - 2)
	{
		px->prev = px->corr;
		px->corr = px->file_fd;
		return ;
	}
	else
	{
		if (px->prev == px->file_fd)
			px->prev = px->p2_fd;
		temp = px->corr;
		px->corr = px->prev;
		px->prev = temp;
	}
	if (pipe(px->corr) == -1)
		error_exit("pipe creation error", px);
}

void	pipex_process(char **argv, char **envp, t_pipex *px, int cmd)
{
	pid_t	pid;
	char	**args;
	char	*path;

	create_pipe(px, cmd);
	pid = fork();
	if (pid == -1)
		error_exit("fork process error", px);
	else if (pid == 0)
	{
		args = create_args(argv[cmd]);
		path = cmd_path(envp, args, px);
		if (dup2(px->prev[0], STDIN_FILENO) < 0)
			error_exit("read fd dup error", px);
		if (dup2(px->corr[1], STDOUT_FILENO) < 0)
			error_exit("write fd dup error", px);
		close_px(px);
		execve(path, args, envp);
		free(path);
		free_array(args);
		error_exit("invalid command", px);
	}
	ft_close(&px->prev[0]);
	ft_close(&px->corr[1]);
	waitpid(pid, NULL, 0);
}
