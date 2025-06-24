/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:34:42 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/24 17:21:50 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
