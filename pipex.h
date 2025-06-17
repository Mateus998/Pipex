/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/17 15:54:34 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

typedef struct s_pipex
{
	int		fd[2];
	char	**cmd1;
	char	*cmdpath1;
	char	**cmd2;
	char	*cmdpath2;
	char	**path;
}			t_pipex;

// frees & errors
void		error_exit(char *msg);
void		free_error(t_pipex *pipex, char *msg);
void		free_array(char **array);
void		free_pipex(t_pipex *pipex);

// parsing
t_pipex		*input_validation(char **argv, char **envp);
char		**find_path(char **envp);
char		*command_path(char *cmd, char **path);
t_pipex		*create_pipex(void);
void file_descriptors_check(char **argv, t_pipex *pipex);

#endif