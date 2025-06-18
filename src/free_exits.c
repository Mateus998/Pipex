/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/18 18:51:28 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	close_px(t_pipex *px)
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
