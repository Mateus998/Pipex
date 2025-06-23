/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/23 12:18:27 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_exit(char *msg, t_pipex *px)
{
	fds_handle(px, 1);
	perror(msg);
	exit(1);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	fds_handle(t_pipex *px, int closing)
{
	if (closing)
	{
		if (px->fd[0] >= 0)
			close(px->fd[0]);
		if (px->fd[1] >= 0)
			close(px->fd[1]);
		if (px->p_fd[0] >= 0)
			close(px->p_fd[0]);
		if (px->p_fd[1] >= 0)
			close(px->p_fd[1]);
	}
	px->fd[0] = -1;
	px->fd[1] = -1;
	px->p_fd[0] = -1;
	px->p_fd[1] = -1;
}
