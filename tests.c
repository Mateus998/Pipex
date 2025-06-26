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

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
    char **a = create_args(argv[1]);
    printf("print array\n");
    print_array(a);
	return (0);
}