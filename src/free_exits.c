/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/26 16:15:38 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_exit(char *msg, t_pipex *px)
{
	fds_handle(px, 1);
	if (msg)
		perror(msg);
	exit(1);
}

void	close_px(t_pipex *px)
{
	if (px->prev[1] >= 0)
		close(px->prev[1]);
	px->prev[1] = -1;
	if (px->corr[0] >= 0)
		close(px->corr[0]);
	px->corr[0] = -1;
	if (px->prev[0] >= 0)
		close(px->prev[0]);
	px->prev[0] = -1;
	if (px->corr[1] >= 0)
		close(px->corr[1]);
	px->corr[1] = -1;
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

void	ft_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

void	fds_handle(t_pipex *px, int closing)
{
	if (closing)
	{
		if (px->file_fd[0] >= 0)
			close(px->file_fd[0]);
		if (px->file_fd[1] >= 0)
			close(px->file_fd[1]);
		if (px->p1_fd[0] >= 0)
			close(px->p1_fd[0]);
		if (px->p1_fd[1] >= 0)
			close(px->p1_fd[1]);
		if (px->p2_fd[0] >= 0)
			close(px->p2_fd[0]);
		if (px->p2_fd[1] >= 0)
			close(px->p2_fd[1]);
	}
	px->file_fd[0] = -1;
	px->file_fd[1] = -1;
	px->p1_fd[0] = -1;
	px->p1_fd[1] = -1;
	px->p2_fd[0] = -1;
	px->p2_fd[1] = -1;
}
