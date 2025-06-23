/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:09 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/23 17:42:58 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	px->file_fd[1] = open(argv[px->argc - 1], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (!px->file_fd[1])
		error_exit("out file open error", px);
}

void	command_validation(int cmd, char **envp, t_pipex *px, char **argv)
{
	char	**args;
	char	*val;

	args = ft_split(argv[cmd], ' ');
	if (!args)
		error_exit("split error", px);
	if (!ft_strchr(args[0], '/'))
	{
		val = cmd_path(envp, args, px);
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
	int		cmd;

	ft_memset(&px, 0, sizeof(t_pipex));
	fds_handle(&px, 0);
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
	while (cmd <= px.argc - 2)
		command_validation(cmd++, envp, &px, argv);
	cmd = px.first_cmd;
	while (cmd <= px.argc - 2)
		pipex_process(argv, envp, &px, cmd++);
	return (0);
}
