/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:25:11 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/17 16:17:03 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_pipex	*input_validation(char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = create_pipex();
    file_descriptors_check(argv, pipex);
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd1 || !pipex->cmd2)
		free_error(pipex, "cmd split error");
	pipex->path = find_path(envp);
	if (!pipex->path)
		free_error(pipex, "env path variable error");
	pipex->cmdpath1 = command_path(pipex->cmd1[0], pipex->path);
	pipex->cmdpath2 = command_path(pipex->cmd2[0], pipex->path);
	if (!pipex->cmdpath1 || !pipex->cmdpath2)
		free_error(pipex, "commad path error");
	return (pipex);
}

void file_descriptors_check(char **argv, t_pipex *pipex)
{
    pipex->fd[0] = open(argv[1], O_RDONLY);
	if (pipex->fd[0] == -1)
		free_error(pipex, "infile open error");
    close(pipex->fd[0]);
    pipex->fd[0] = -1;
	pipex->fd[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
    if (pipex->fd[1] == -1)
		free_error(pipex, "outfile open error");
    close(pipex->fd[1]);
    pipex->fd[1] = -1;
}

t_pipex	*create_pipex(void)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error_exit("t_pipex allocation error");
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->cmdpath1 = NULL;
	pipex->cmdpath2 = NULL;
	pipex->path = NULL;
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	return (pipex);
}

char	**find_path(char **envp)
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

char	*command_path(char *cmd, char **path)
{
	int		i;
	char	*dirname;
	char	*pathname;

	i = 0;
	while (path[i])
	{
		dirname = ft_strjoin(path[i], "/");
		pathname = ft_strjoin(dirname, cmd);
		free(dirname);
		if (!access(pathname, X_OK))
			return (pathname);
		free(pathname);
		i++;
	}
	return (NULL);
}
