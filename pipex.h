/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:15 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/14 16:33:49 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"

typedef struct s_pipex
{
	int		file_fd[2];
	int		p1_fd[2];
	int		p2_fd[2];
	pid_t pid;
	int processes;
	int exit_status;
	int		argc;
	int		first_cmd;
	int		*corr;
	int		*prev;
	char	**args;
	char	*path;
}			t_pipex;

// frees & errors
void		error_exit(char *msg, t_pipex *px);
void		free_array(char **array);
void		close_px(t_pipex *px);
void		fds_handle(t_pipex *px, int closing);
void		ft_close(int *fd);

// utils
char		**px_split(char const *s);
int			px_strncmp(const char *s1, const char *s2, size_t n);
void		here_doc_fill(char **argv, t_pipex *px);

// process
void		pipex_process(char **envp, t_pipex *px, int proc, char **argv);
char		*cmd_path(char **envp, t_pipex *px);

#endif