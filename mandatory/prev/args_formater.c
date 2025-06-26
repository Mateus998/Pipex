/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_formater.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:01:10 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/26 11:42:47 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../pipex.h"

int	join_arg(char **str, char c)
{
	char	*join;
	char	chr[2];

	chr[0] = c;
	chr[1] = '\0';
	join = ft_strjoin(*str, chr);
    return (free(str), 0);
	free(*str);
	*str = join;
	return (1);
}

int realloc_array(char ***array, char *str)
{
	int		i;
	char	**new;

    if (!str)
    {
        return (0);
    }
	if (!*array)
	{
		new = (char **)malloc(2 * sizeof(char *));
        if (!new)
            return (free_array(array), free(str), 0);
		new[0] = ft_strdup(str);
        if (!new[0])
            return (free_array(array), free(str), free(new), 0);
		new[1] = NULL;
	}
    else
    {
        i = 0;
        while ((*array)[i])
            i++;
        new = (char **)malloc((i + 2) * sizeof(char *));
        if (!new)
            return (free_array(array), free(str), 0);
        i = 0;
        while ((*array)[i])
        {
            new[i] = ft_strdup((*array)[i]);
            if (!new[i++])
                return (free_array(array), free(str), free_array(new), 0);
        }
        new[i] = ft_strdup(str);
        if (!new[i])
            return (free_array(array), free(str), free_array(new), 0);
        new[++i] = NULL;
        i = 0;
        while((*array)[i])
            free((*array)[i++]);
        free(*array);
    }
	free(str);
    *array = new;
	return (1);
}

char	**create_args(char *s)
{
	int		i;
	char	*arg;
	char	**args;
	int status;

	arg = NULL;
	args = NULL;
	status = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'' && status == 1)
				status = join_arg(&arg, s[i++]);
			if (s[i])
				i++;
		}
		else if (s[i] == ' ')
		{
			while (s[i] && s[i] == ' ' && status == 1)
				i++;
            status = realloc_array(&args, arg);
			arg = NULL;
		}
		else
			while (s[i] && s[i] != ' ' && s[i] != '\'' && status == 1)
				status = join_arg(&arg, s[i++]);
		if (status != 1)
			return (arg_error(status), NULL);
	}
    realloc_array(&args, arg);
	free(arg);
    return (args);
}
