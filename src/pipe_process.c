/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/11 10:24:00 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	here_doc_fill(char **argv, t_pipex *px)
{
	char	*line;
	size_t	lim;

	if (px->argc < 6)
	{
		ft_putendl_fd("5 arguments minimum", 2);
		exit(1);
	}
	if (pipe(px->file_fd) < 0)
		error_exit("pipe error", px);
	lim = ft_strlen(argv[2]);
	line = get_next_line(STDIN_FILENO);
	while (line && px_strncmp(line, argv[2], lim))
	{
		ft_putstr_fd(line, px->file_fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	ft_close(&px->file_fd[1]);
	px->first_cmd = 3;
	px->file_fd[1] = open(argv[px->argc - 1], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (px->file_fd[1] == -1)
		perror(argv[px->argc - 1]);
}

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

void	process_exit(t_pipex *px)
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

void	pipex_process(char **envp, t_pipex *px, int cmd)
{
	pid_t	pid;

	create_pipe(px, cmd);
	pid = fork();
	if (pid == -1)
		error_exit("fork process error", px);
	else if (pid == 0)
	{
		if (dup2(px->prev[0], STDIN_FILENO) == -1)
			error_exit(NULL, px);
		dup2(px->corr[1], STDOUT_FILENO);
		close_px(px);
		execve(px->path, px->args, envp);
		process_exit(px);
	}
	ft_close(&px->prev[0]);
	ft_close(&px->corr[1]);
}
