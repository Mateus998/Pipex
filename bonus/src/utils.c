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
	px->file_fd[0] = open(file1, O_RDONLY);
	if (px->file_fd[0] == -1)
		error_exit("infile open error");
	px->file_fd[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->file_fd[1] == -1)
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
	error_exit("path var NULL");
	return (NULL);
}

char	*cmd_path(char **envp, char **args)
{
	int		i;
	char	*dirname;
	char	*pathname;
	char	**path;

	if (!args)
		error_exit("command split error");
	path = find_path_var(envp);
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
	free_array(args);
	error_exit("invalid command");
	return (NULL);
}
