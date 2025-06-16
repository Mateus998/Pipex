#ifndef PIPEX_H
#define PIPEX_H

# include "libft/libft.h"

typedef struct s_pipex
{
    int fd1;
    int fd2;
    char **cmd1;
    char *cmdpath1;
    char **cmd2;
    char *cmdpath2;
    char **path;
} t_pipex;

// frees & errors
void error_exit(char *msg);
void free_error(t_pipex *pipex, char *msg);
void free_array(char **array);
void free_pipex(t_pipex *pipex);

// parsing
t_pipex *input_validation(char **argv, char **envp);
char **find_path(char **envp);
char *command_path(char *cmd, char **path);
t_pipex *create_pipex(void);

#endif