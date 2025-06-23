/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:15 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/19 17:21:10 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_pipex
{
	int	file_fd[2];
	int	p1_fd[2];
	int	p2_fd[2];
	int	argc;
	int first_cmd;
	int *corr;
	int *prev;
}		t_pipex;

// frees & errors
void	error_exit(char *msg);
void	free_array(char **array);
void	close_px(t_pipex *px);
void free_gnl(int fd);

// utils
void	open_files(char *file1, char *file2, t_pipex *px);
char	**find_path_var(char **envp);
char	*cmd_path(char **envp, char **args);

// process
void	pipex_process(char **argv, char **envp, t_pipex *px, int proc);
void create_pipe(t_pipex *px, int cmd);

#endif