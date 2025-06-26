/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_formater.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:07:07 by mateferr          #+#    #+#             */
/*   Updated: 2025/06/26 19:05:08 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	join_arg(char **str, char c)
{
	char	*join;
	char	chr[2];

	chr[0] = c;
	chr[1] = '\0';
	join = ft_strjoin(*str, chr);
	if (!join)
		return (free(*str), 0);
	free(*str);
	*str = join;
	return (1);
}

static int	ft_realloc(char **array, char ***new, char *str)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	*new = (char **)malloc((i + 2) * sizeof(char *));
	if (!*new)
		return (free_array(array), free(str), 0);
	i = 0;
	while (array[i])
	{
		(*new)[i] = ft_strdup(array[i]);
		if (!(*new)[i++])
			return (free_array(array), free(str), free_array(*new), 0);
	}
	(*new)[i] = ft_strdup(str);
	if (!(*new)[i])
		return (free_array(array), free(str), free_array(*new), 0);
	(*new)[++i] = NULL;
	free_array(array);
	return (1);
}

static int	realloc_array(char ***array, char **str)
{
	char	**new;
	int		status;

	status = 1;
	new = NULL;
	if (!str || !*str)
		return (1);
	else if (!*array)
	{
		new = (char **)malloc(2 * sizeof(char *));
		if (!new)
			return (free_array(*array), free(*str), 0);
		new[0] = ft_strdup(*str);
		if (!new[0])
			return (free_array(*array), free(*str), free(new), 0);
		new[1] = NULL;
	}
	else
		status = ft_realloc(*array, &new, *str);
	if (status != 1)
		return (status);
	free(*str);
	*str = NULL;
	*array = new;
	return (1);
}

static int	str_loop(int *i, char *s, char **arg, char ***args)
{
	int	status;

	status = 1;
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'' && status == 1)
			status = join_arg(arg, s[(*i)++]);
		if (s[*i])
			(*i)++;
	}
	else if (s[*i] == ' ')
	{
		while (s[*i] && s[*i] == ' ' && status == 1)
			(*i)++;
		status = realloc_array(args, arg);
	}
	else
		while (s[*i] && s[*i] != ' ' && s[*i] != '\'' && status == 1)
			status = join_arg(arg, s[(*i)++]);
	if (status != 1)
		free_array(*args);
	return (status);
}

char	**create_args(char *s)
{
	int		i;
	char	*arg;
	char	**args;

	arg = NULL;
	args = NULL;
	i = 0;
	quotes_count(s);
	if (empty_array_check(s))
		return (empty_array());
	while (s[i])
	{
		if (str_loop(&i, s, &arg, &args) != 1)
			return (ft_putendl_fd("args allocation1 error", 2), NULL);
	}
	if (realloc_array(&args, &arg) != 1)
		return (ft_putendl_fd("args allocation2 error", 2), NULL);
	return (args);
}
