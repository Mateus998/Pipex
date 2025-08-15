/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:21:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/26 19:17:55 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	px_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (s1[i] == '\n' && i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static char	**find_path_var(char **envp, t_pipex *px)
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
			if (!temp)
				error_exit("allocation error", px);
			path = ft_split(temp, ':');
			free(temp);
			if (!path)
				error_exit("allocation error", px);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	*path_validate(char *path, char *cmd, t_pipex *px)
{
	char	*dirname;
	char	*pathname;

	dirname = ft_strjoin(path, "/");
	if (!dirname)
		error_exit("allocation error", px);
	pathname = ft_strjoin(dirname, cmd);
	free(dirname);
	if (!pathname)
		error_exit("allocation error", px);
	if (!access(pathname, X_OK))
		return (pathname);
	free(pathname);
	return (NULL);
}

char	*cmd_path(char **envp, t_pipex *px)
{
	int		i;
	char	**path;
	char	*pathname;

	if (!px->args)
		error_exit(NULL, px);
	pathname = NULL;
	if (!ft_strchr(px->args[0], '/') && *envp)
	{
		path = find_path_var(envp, px);
		i = 0;
		while (path && !pathname && path[i])
			pathname = path_validate(path[i++], px->args[0], px);
		free_array(path);
	}
	if (!pathname)
	{
		pathname = ft_strdup(px->args[0]);
		if (!pathname)
			error_exit("allocation error", px);
	}
	return (pathname);
}
