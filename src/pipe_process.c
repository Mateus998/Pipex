/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/18 10:17:55 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	create_pipe(t_pipex *px, int cmd)
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

static void	child_process_file_open(t_pipex *px, int cmd, char **argv)
{
	if (cmd == px->first_cmd && ft_strncmp("here_doc", argv[1], 8))
	{
		px->file_fd[0] = open(argv[1], O_RDONLY);
		if (px->file_fd[0] == -1)
			error_exit("open infile error", px);
	}
	else if (cmd == px->argc - 2)
	{
		if (ft_strncmp("here_doc", argv[1], 8))
			px->file_fd[1] = open(argv[px->argc - 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			px->file_fd[1] = open(argv[px->argc - 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (px->file_fd[1] == -1)
			error_exit("open outfile error", px);
	}
}

static void	process_exit(t_pipex *px)
{
	close(0);
	close(1);
	ft_putstr_fd(px->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	if (px->path)
		free(px->path);
	free_array(px->args);
	exit(127);
}

static void	fd_dup_execve(t_pipex *px, char **envp)
{
	if (dup2(px->prev[0], STDIN_FILENO) == -1)
		error_exit(NULL, px);
	dup2(px->corr[1], STDOUT_FILENO);
	close_px(px);
	if (!px->args[0])
		process_exit(px);
	execve(px->path, px->args, envp);
	process_exit(px);
}

void	pipex_process(char **envp, t_pipex *px, int cmd, char **argv)
{
	create_pipe(px, cmd);
	px->pid = fork();
	px->processes++;
	if (px->pid == -1)
		error_exit("fork process error", px);
	else if (px->pid == 0)
	{
		child_process_file_open(px, cmd, argv);
		fd_dup_execve(px, envp);
	}
	ft_close(&px->prev[0]);
	ft_close(&px->corr[1]);
}
