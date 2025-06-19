/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:21:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/19 17:48:48 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_files(char *file1, char *file2, t_pipex *px)
{
	px->fd[0] = open(file1, O_RDONLY);
	if (px->fd[0] == -1)
		error_exit("infile open error");
	px->fd[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd[1] == -1)
		error_exit("outfile open error");
}

char	**find_path_var(char **envp)
{
	int		i;
	char	*temp;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			temp = ft_strtrim(envp[i], "PATH=");
			path = ft_split(temp, ':');
			free(temp);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*cmd_path(char **envp, char **args)
{
	int		i;
	char	*dirname;
	char	*pathname;
	char	**path;

	path = find_path_var(envp);
	if (!path)
		return (ft_putendl_fd("path var NULL", 2), NULL);
	i = 0;
	while (path[i])
	{
		dirname = ft_strjoin(path[i], "/");
		pathname = ft_strjoin(dirname, args[0]);
		free(dirname);
		if (!access(pathname, X_OK))
			return (pathname);
		free(pathname);
		i++;
	}
	ft_putendl_fd(args[0], 2);
	free_array(args);
	return (ft_putendl_fd("command not found", 2), NULL);
}

void	fork_process(char *cmd, char **envp, t_pipex *px, int step)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		error_exit("exec args error");
	path = cmd_path(envp, args);
	if (!path)
		error_exit("exec path error");
	duplicate_fds(step, px);
	close_px(px);
	execve(path, args, envp);
	free(path);
	free_array(args);
}

void	duplicate_fds(int step, t_pipex *px)
{
	if (!step)
	{
		if (dup2(px->fd[0], STDIN_FILENO) < 0)
			error_exit("read infile dup error");
		if (dup2(px->p1_fd[1], STDOUT_FILENO) < 0)
			error_exit("begin write dup error");
	}
	else
	{
		if (step % 2 == 0)
		{
			if (dup2(px->p2_fd[0], STDIN_FILENO) < 0)
				error_exit("end read p2_fd dup error");
		}
		else
		{
			if (dup2(px->p1_fd[0], STDIN_FILENO) < 0)
				error_exit("end read p1_fd dup error");
		}
		if (dup2(px->fd[1], STDOUT_FILENO) < 0)
			error_exit("write outfile dup error");
	}
}

