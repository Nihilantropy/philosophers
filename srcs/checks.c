/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:14:32 by crea              #+#    #+#             */
/*   Updated: 2024/05/18 18:27:31 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_checks_utils(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit_str(argv[i]))
		{
			printf(ERR_ARG_FORM);
			return (0);
		}
		if (!check_positive_input(argv[i]))
		{
			printf(ERR_ZERO_INPUT);
			return (0);
		}
		i++;
	}
	if (!max_thread(argv[1]))
	{
		printf(ERR_MAX_THREAD);
		return (0);
	}
	return (1);
}

int	ft_checks(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(ERR_NBR_ARG);
		return (0);
	}
	if (!ft_checks_utils(argv))
		return (0);
	return (1);
}
