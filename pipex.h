/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/18 19:19:44 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

typedef struct s_pipex
{
	int	fd[2];
	int	p_fd[2];
}		t_pipex;

// frees & errors
void	error_exit(char *msg);
void	free_array(char **array);
void	close_px(t_pipex *px);

// utils
void	open_files(char *file1, char *file2, t_pipex *px);
char	**find_path_var(char **envp);
char	*cmd_path(char **envp, char **args);

// process
void	pipe_process(void);
void	read_process(char *cmd, char **envp, t_pipex *px);
void	write_process(char *cmd, char **envp, t_pipex *px);

#endif