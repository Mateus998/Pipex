#include "pipex.h"

void print_array(char **a)
{
    if(!a)
    {
        printf("NULL print\n");
        return;
    }
    int i = 0;
    while(a[i])
	{
        ft_printf("%s\n", a[i++]);
	}
	i = 0;
	while(a[i])
	{
        free(a[i++]);
	}
    free(a);
}

int	main()
{
	int p[2];
    pipe(p);
    write(p[1], "ola", 3);
    char *buff = malloc(3);
    read(p[0], buff, 3);
    printf("%s\n", buff);
    free(buff);
	return (0);
}
