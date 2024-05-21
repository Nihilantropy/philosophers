/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:24 by crea              #+#    #+#             */
/*   Updated: 2024/05/14 13:11:24 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
		if (str[i] == '-' || str[i] == '+')
			return (0);
	}
	return (1);
}

int	check_positive_input(char *str)
{
	long	nbr;

	nbr = ft_atol(str);
	if (nbr <= 0 || nbr > 2147483647)
		return (0);
	return (1);
}

int	max_thread(char *str)
{
	if (ft_atoi(str) >= 126269)
		return (0);
	return (1);
}
