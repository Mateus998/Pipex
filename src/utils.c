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
}
