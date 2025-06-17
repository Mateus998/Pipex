/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:31:58 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/17 16:58:56 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

void pipe_process(t_pipex *pipex)
{
    pid_t p;
    
    if (pipe(pipex->fd) == -1)
        free_error(pipex, "pipe func error");
    p = fork();
    if (p == -1)
        free_error(pipex, "fork func error");
    if (p == 0)
    {
        //child process - reads information
        child_process(pipex);
    }
    else
    {
        //parent process - writes information    
        parent_process(pipex);
    }
}

void child_process(t_pipex *pipex)
{
    close(pipex->fd[1]);
    //read and exec first command?
    close(pipex->fd[0]);
}

void parent_process(t_pipex *pipex)
{
    close(pipex->fd[0]);
    //write second command
    close(pipex->fd[1]);
}
