/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:41:24 by crea              #+#    #+#             */
/*   Updated: 2024/05/18 17:00:13 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	choose_routine(t_table *table, pthread_t *thread)
{
	int	i;

	i = 0;
	if (pthread_create(&thread[table->nbr_of_philo], NULL, observer, (void *)table))
	{
		printf(ERR_OBS_THREAD_CREATE);
		return (0);
	}
	usleep(100);
	while (i < table->nbr_of_philo)
	{
		if (table->nbr_of_philo % 2 == 0)
		{
			if (pthread_create(&thread[i], NULL,
					philo_routine_even, (void *)table))
			{
				printf(ERR_PHILO_THREAD_CREATE);
				return (0);
			}
		}
		else
		{
			if (pthread_create(&thread[i], NULL,
					philo_routine_odd, (void *)table))
			{
				printf(ERR_PHILO_THREAD_CREATE);
				return (0);
			}
		}
		i++;
	}
	i = 0;
	while (i <= table->nbr_of_philo)
		pthread_join(thread[i++], NULL);
	destroy_mutexes(table);
	free(thread);
	free_list(&table->philo);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	*thread;

	if (!ft_checks(argc, argv))
		return (0);
	printf("checks passed\n");
	if (!init_table(&table, argv))
		return (0);
	printf(TABLE_READY);
	thread = malloc(sizeof(pthread_t) * (ft_atoi(argv[1]) + 1));
	if (!thread)
	{
		printf(ERR_THREAD_ALLOC);
		return (0);
	}
	if (!choose_routine(&table, thread))
	{
		free(thread);
		destroy_mutexes(&table);
		free_list(&table.philo);
		return (0);
	}
	return (0);
}
