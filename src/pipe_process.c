/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/26 19:28:13 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	quotes_count(char *s)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			quotes++;
		i++;
	}
	if (quotes % 2 != 0)
		ft_putendl_fd("Open quotes!!!", 2);
}

void	here_doc_fill(char **argv, t_pipex *px)
{
	char	*line;
	size_t	lim;

	if (pipe(px->file_fd) < 0)
		error_exit("pipe error", px);
	lim = ft_strlen(argv[2]);
	line = get_next_line_px(STDIN_FILENO, argv[2]);
	while (line && ft_strncmp(line, argv[2], lim))
	{
		ft_putstr_fd(line, px->file_fd[1]);
		free(line);
		line = get_next_line_px(STDIN_FILENO, argv[2]);
	}
	free(line);
	ft_close(&px->file_fd[1]);
	px->first_cmd = 3;
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

void	process_exit(char **args, char *path)
{
	close(0);
	close(1);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(args[0], 2);
	if (path)
		free(path);
	free_array(args);
	exit(127);
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
		path = cmd_path(envp, args);
		dup2(px->prev[0], STDIN_FILENO);
		dup2(px->corr[1], STDOUT_FILENO);
		close_px(px);
		if (!path)
			process_exit(args, NULL);
		execve(path, args, envp);
		process_exit(args, path);
	}
	ft_close(&px->prev[0]);
	ft_close(&px->corr[1]);
	waitpid(pid, NULL, 0);
}
