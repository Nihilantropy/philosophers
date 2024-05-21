/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:47:12 by crea              #+#    #+#             */
/*   Updated: 2024/05/20 16:12:26 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_table(t_table *table, char **argv)
{
	table->nbr_of_philo = ft_atoi(argv[1]);
	table->philo_index = 0;
	if (argv[5])
		table->nbr_of_meals = ft_atoi(argv[5]);
	else
		table->nbr_of_meals = -1;
	table->first_meal = true;
	if (pthread_mutex_init(&table->is_writing, NULL) 
			|| pthread_mutex_init(&table->is_sitting, NULL)
				|| pthread_mutex_init(&table->death, NULL))
		return (0);
	table->dinner_start = 0;
	table->dinner_end = false;
	table->philo = NULL;
	if (!create_philo_list(&table->philo, argv))
		return (0);
	printf(PHILO_LIST_READY);
	return (1);
}

void	destroy_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->is_writing);
	pthread_mutex_destroy(&table->is_sitting);
	pthread_mutex_destroy(&table->death);
}
