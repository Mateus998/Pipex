/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:15 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/24 17:26:22 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

typedef struct s_pipex
{
	int	file_fd[2];
	int	p1_fd[2];
	int	p2_fd[2];
	int	argc;
	int	first_cmd;
	int	*corr;
	int	*prev;
}		t_pipex;

// frees & errors
void	error_exit(char *msg, t_pipex *px);
void	free_array(char **array);
void	close_px(t_pipex *px);
void	fds_handle(t_pipex *px, int closing);
void	ft_close(int *fd);

// utils
void	open_outfile(t_pipex *px, char *file);
char	**find_path_var(char **envp, t_pipex *px, char **args);
char	*cmd_path(char **envp, char **args, t_pipex *px);
char	*get_next_line_px(int fd, char *limiter);
char	*path_validate(char **path, int i, char *cmd);

// process
void	pipex_process(char **argv, char **envp, t_pipex *px, int proc);
void	create_pipe(t_pipex *px, int cmd);
void	here_doc_fill(char **argv, t_pipex *px);

#endif