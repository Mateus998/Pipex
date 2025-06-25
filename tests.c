#include "pipex.h"

static int	ft_chr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

void	cmd_format_handle(char *cmd)
{
	char	*first;
	char	*rest;

	first = ft_substr(cmd, 0, ft_chr(cmd, ' '));
	rest = ft_strdup(ft_strchr(cmd, '\''));
	// char *rest = ft_strdup(&cmd[ft_chr(cmd, ' ') + 1]);
	printf("[%s]\n", first);
	free(first);
	printf("[%s]\n", rest);
	free(rest);
	// int i = 0;
	// while(split[i])
	// 	printf("%s\n", split[i++]);
	// // printf("\n");
	// i = 0;
	// while(split[i])
	//     free(split[i++]);
	// free(split);
}

// fora de aspas - espaco e separador
// dentro de aspas - espaco e caracter
static void	count_words(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'') // dentro aspas
		{
			// concatenar chars
			ft_printf("a[%c", s[i++]);
			while (s[i] && s[i] != '\'')
				ft_printf("%c", s[i++]);
			ft_printf("%c]\n", s[i]);
			if (s[i])
				i++;
		}
		else if (s[i] == ' ') // next arg
		{
			// separar args
			ft_printf("n[%c", s[i++]);
			while (s[i] && s[i] == ' ')
				ft_printf("%c", s[i++]);
			ft_printf("]\n");
		}
		else // fora aspas
		{
			// concatecar chars
			ft_printf("f[%c", s[i++]);
			while (s[i] && s[i] != ' ' && s[i] != '\'')
				ft_printf("%c", s[i++]);
			if (s[i] == '\'')
				ft_printf("]\n");
			else
			{
				ft_printf("%c]\n", s[i]);
				if (s[i])
					i++;
			}
		}
	}
}

static void	join_arg(char **str, char c)
{
	char	*join;
	char	chr[2];

	chr[0] = c;
	chr[1] = '\0';
	join = ft_strjoin(*str, chr);
    //error handle
	free(*str);
	*str = join;
}

void realloc_array(char ***array, char *str)
{
	int		i;
	char	**new;

    if (!str)
        return ;
	if (!*array)
	{
		new = (char **)malloc(2 * sizeof(char *));
        if (!new)
            ft_printf("error\n");
		new[0] = ft_strdup(str);
        if (!new[0])
            ft_printf("error\n");
		new[1] = NULL;
	}
    else
    {
        i = 0;
        while ((*array)[i])
            i++;
        new = (char **)malloc((i + 2) * sizeof(char *));
        if (!new)
            ft_printf("error\n");
        i = 0;
        while ((*array)[i])
        {
            new[i] = ft_strdup((*array)[i]);
            if (!new[i++])
                ft_printf("error\n");
        }
        new[i] = ft_strdup(str);
        if (!new[i])
            ft_printf("error\n");
        new[++i] = NULL;
        i = 0;
        while((*array)[i])
            free((*array)[i++]);
        free(*array);
    }
    *array = new;
}

char	**create_args(char *s)
{
	int		i;
	char	*arg;
	char	**args;

	arg = NULL;
	args = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				join_arg(&arg, s[i++]);
			if (s[i])
				i++;
		}
		else if (s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
            realloc_array(&args, arg);
			free(arg);
			arg = NULL;
		}
		else
			while (s[i] && s[i] != ' ' && s[i] != '\'')
				join_arg(&arg, s[i++]);
	}
    realloc_array(&args, arg);
	free(arg);
    return (args);
}

void print_array(char **a)
{
    if(!a)
    {
        printf("NULL print\n");
        return;
    }
    int i = 0;
    while(a[i])
        ft_printf("%s\n", a[i++]);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
    char **a = create_args(argv[1]);
    printf("\nprint array\n");
    print_array(a);
    int i = 0;
    while(a[i])
        free(a[i++]);
    free(a);
	return (0);
}