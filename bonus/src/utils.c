/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:21:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/23 16:10:17 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_files(char *file1, char *file2, t_pipex *px)
{
	px->file_fd[0] = open(file1, O_RDONLY);
	if (px->file_fd[0] == -1)
		error_exit("infile open error", px);
	px->file_fd[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->file_fd[1] == -1)
		error_exit("outfile open error", px);
}

char	**find_path_var(char **envp, t_pipex *px)
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
	error_exit("path var NULL", px);
	return (NULL);
}

char	*cmd_path(char **envp, char **args, t_pipex *px)
{
	int		i;
	char	*dirname;
	char	*pathname;
	char	**path;

	if (!args)
		error_exit("command split error", px);
	if (ft_strchr(args[0], '/'))
		return (ft_strdup(args[0]));
	path = find_path_var(envp, px);
	i = 0;
	while (path[i])
	{
		dirname = ft_strjoin(path[i++], "/");
		pathname = ft_strjoin(dirname, args[0]);
		free(dirname);
		if (!access(pathname, X_OK))
		{
			free_array(path);
			return (pathname);
		}
		free(pathname);
	}
	free_array(path);
	return (NULL);
}
