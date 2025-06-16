#include "../pipex.h"

void error_exit(char *msg)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd(msg, 2);
    exit(1);
}

void free_error(t_pipex *pipex, char *msg)
{
    free_pipex(pipex);
    error_exit(msg);
}

void free_pipex(t_pipex *pipex)
{
    if (pipex->cmdpath1)
        free(pipex->cmdpath1);
    if (pipex->cmdpath2)
        free(pipex->cmdpath2);
    if (pipex->cmd1)
        free_array(pipex->cmd1);
    if (pipex->cmd2)
        free_array(pipex->cmd2);
    if (pipex->path)
        free_array(pipex->path);
    if (pipex->fd1 != -1)
        close(pipex->fd1);
    if (pipex->fd2 != -1)
        close(pipex->fd2);
    free(pipex);
}

void free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
