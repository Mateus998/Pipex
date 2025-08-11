/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:38:15 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/11 10:21:49 by mateferr         ###   ########.fr       */
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
char		*cmd_path(char **envp, t_pipex *px);
// char		*get_next_line_px(int fd, char *limiter);
char		**px_split(char const *s);
int			px_strncmp(const char *s1, const char *s2, size_t n);
void		file_read(t_pipex *px, char *file1, char *file2);

// process
void		pipex_process(char **envp, t_pipex *px, int proc);
void		create_pipe(t_pipex *px, int cmd);
void		here_doc_fill(char **argv, t_pipex *px);

#endif