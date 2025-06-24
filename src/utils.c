/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:21:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/24 18:11:20 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_outfile(t_pipex *px, char *file)
{
	if (px->first_cmd == 2)
		px->file_fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (px->first_cmd == 3)
		px->file_fd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (px->file_fd[1] == -1)
		perror(file);
}

char	**find_path_var(char **envp, t_pipex *px, char **args)
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
	free_array(args);
	error_exit("path var NULL", px);
	return (NULL);
}

char	*cmd_path(char **envp, char **args, t_pipex *px)
{
	int		i;
	char	**path;
	char *pathname;

	if (!args)
		error_exit("command split error", px);
	pathname = NULL;
	if (!ft_strchr(args[0], '/'))
	{
		path = find_path_var(envp, px, args);
		i = 0;
		while (!pathname && path[i])
			pathname = path_validate(path, i++, args[0]);
		free_array(path);
	}
	if (!pathname)
	{
		pathname = ft_strdup(args[0]);
		if (!pathname)
			error_exit("path strdup error", px);
	}		
	return (pathname);
}

char *path_validate(char **path, int i, char *cmd)
{
	char	*dirname;
	char	*pathname;
	
	dirname = ft_strjoin(path[i], "/");
	pathname = ft_strjoin(dirname, cmd);
	free(dirname);
	if (!access(pathname, X_OK))
		return (pathname);
	free(pathname);
	return (NULL);
}
