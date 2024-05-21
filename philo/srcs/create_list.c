/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:19:06 by crea              #+#    #+#             */
/*   Updated: 2024/05/20 16:11:51 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->dead_lock, NULL)
		|| pthread_mutex_init(&philo->right_fork, NULL))
		return (0);
	return (1);
}

int	init_philo(t_philo *philo, char **argv, int index)
{
	philo->index = index + 1;
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->last_meal = 0;
	philo->first_meal = true;
	philo->is_sleeping = false;
	philo->is_thinking = false;
	philo->is_eating = false;
	philo->is_dead = false;
	philo->current_meal = 0;
	if (!init_mutex(philo))
	{
		printf(ERR_PHILO_MUTEX);
		return (0);
	}
	return (1);
}

int	create_philo_list(t_philo **philo, char **argv)
{
	int		i;
	t_philo	*new_philo;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		new_philo = malloc(sizeof(t_philo));
		if (!new_philo)
		{
			printf(ERR_PHILO_ALLOC);
			return (0);
		}
		if (!init_philo(new_philo, argv, i))
		{
			printf(ERR_INIT_PHILO);
			return (0);
		}
		if (!*philo)
		{
			new_philo->next = new_philo;
			new_philo->prev = new_philo;
			*philo = new_philo;
		}
		else
		{
			new_philo->next = *philo;
			new_philo->prev = (*philo)->prev;
			(*philo)->prev->next = new_philo;
			(*philo)->prev = new_philo;
		}
		i++;
	}
	return (1);
}
