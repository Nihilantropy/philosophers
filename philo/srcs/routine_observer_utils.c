/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_observer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:10:36 by crea              #+#    #+#             */
/*   Updated: 2024/05/23 17:10:38 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_meals_utils(t_table *table)
{
	pthread_mutex_lock(&table->is_writing);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_writing);
		pthread_mutex_lock(&table->death);
		return ;
	}
	table->dinner_end = true;
	printf("All philo have eaten %d meals\n", table->nbr_of_meals);
	printf("Dinner has ended at %llu\n", get_time() - table->dinner_start);
	pthread_mutex_unlock(&table->is_writing);
}

void	check_death_utils(t_table *table, t_philo *current_philo,
				long long current_time)
{
	int	index;

	pthread_mutex_lock(&table->is_writing);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_writing);
		return ;
	}
	index = current_philo->index;
	current_philo->is_dead = true;
	printf("%llu %d died\n", current_time - table->dinner_start, index);
	table->dinner_end = true;
	printf("Dinner have ended at %llu\n", current_time - table->dinner_start);
	printf("Death check\n");
	pthread_mutex_unlock(&table->is_writing);
}
