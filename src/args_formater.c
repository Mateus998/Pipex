/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_formater.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:01:10 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/25 20:05:39 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

static void realloc_array(char ***array, char *str)
{
	int		i;
	char	**new;

    if (!str)
    {
        return ;
    }
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
