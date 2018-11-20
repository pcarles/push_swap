/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 00:18:58 by pcarles           #+#    #+#             */
/*   Updated: 2018/10/30 18:44:06 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include "checker.h"

static int	parse_flags(int const ac, char const **av, int *options)
{
	int		i;

	*options = 0;
	i = 1;
	while (i < ac && *av[i] == '-')
	{
		if (!ft_strcmp(av[i], "-p"))
			*options |= FLAG_PRINT;
		else if (!ft_strcmp(av[i], "--csv"))
			*options |= FLAG_CSV;
		else if (!ft_strcmp(av[i], "-i"))
			*options |= FLAG_INTERACTIVE;
		else if (ft_isdigit(av[i][1]))
			break ;
		else
			return (-1);
		i++;
	}
	return (i);
}

int			main(int const ac, char const **av)
{
	int		options;
	int		res;
	int		op_counter;
	int		list_len;
	t_node	*lst_a;
	t_node	*lst_b;

	lst_a = NULL;
	lst_b = NULL;
	res = parse_flags(ac, av, &options);
	if (res == -1)
		exit_error("usage: ./checker [options] numbers...\
\n  options:\n    -p, Print the two lists\n");
	res = parse(ac, av, res, &lst_a);
	if (res == -2)
		exit_error("parse error");
	list_len = get_list_len(lst_a);
	if (!lst_a)
		exit_error("empty list");
	op_counter = read_op(&lst_a, &lst_b, options);
	if (op_counter == -1)
		exit_error("invalid command");
	print_return(lst_a, lst_b, options, op_counter);
	free_lst(lst_a);
	free_lst(lst_b);
	return (0);
}
