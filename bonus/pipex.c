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

void free_gnl(int fd)
{
	char *line;

	if (dup2(fd, STDIN_FILENO) < 0)
		error_exit("end free dup error");
	close(fd);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

void here_doc_fill(char **argv, t_pipex *px)
{
	char *line;
	size_t lim;

	if (pipe(px->file_fd) < 0)
		error_exit("pipe error");
	if (pipe(px->p1_fd) < 0)
		error_exit("pipe error");
	lim = ft_strlen(argv[2]);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, argv[2], lim))
	{
		ft_putstr_fd(line, px->file_fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free_gnl(px->p1_fd[1]);
	close(px->p1_fd[0]);
	close(px->file_fd[1]);
	px->file_fd[1] = open(argv[px->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!px->file_fd[1])
		error_exit("out file open error");
}
//check open fds at exit error need closing
int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		cmd;

	ft_memset(&px, 0, sizeof(t_pipex));
	px.argc = argc;
	if (!ft_strncmp("here_doc", argv[1], 8))
	{
		here_doc_fill(argv, &px);
		px.first_cmd = 3;
	}
	else
	{
		open_files(argv[1], argv[argc - 1], &px);
		px.first_cmd = 2;
	}
	cmd = px.first_cmd;
	while(cmd <= px.argc - 2)
		pipex_process(argv, envp, &px, cmd++);
	return (0);
}
