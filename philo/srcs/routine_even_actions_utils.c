/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_even_actions_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:24:28 by crea              #+#    #+#             */
/*   Updated: 2024/05/22 17:30:50 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_first_meal_even_utils(t_table *table, t_philo *current_philo,
			long long current_time)
{
	long long	dinner_start;

	dinner_start = table->dinner_start;
	current_philo->is_dead = true;
	pthread_mutex_lock(&table->is_writing);
	printf("%llu %d died\n", current_time - dinner_start, current_philo->index);
	printf("Dinner have ended at %llu\n", current_time - table->dinner_start);
	printf("Death at first meal check\n");
	pthread_mutex_unlock(&table->is_writing);
	table->dinner_end = true;
}

void	eating_even_utils(t_table *table, t_philo *current_philo)
{
	long long	current_time;
	long long	dinner_start;
	int			index;

	dinner_start = table->dinner_start;
	current_time = get_time();
	index = current_philo->index;
	printf("%llu %d has taken a fork\n", current_time - dinner_start, index);
	printf("%llu %d has taken a fork\n", current_time - dinner_start, index);
	printf("%llu %d is eating\n", current_time - dinner_start, index);
	pthread_mutex_unlock(&table->is_writing);
	current_philo->last_meal = current_time;
	usleep(current_philo->time_to_eat * 1000);
	if (table->nbr_of_meals != -1)
		current_philo->current_meal++;
	current_philo->first_meal = false;
	current_philo->is_eating = false;
	current_philo->is_sleeping = true;
}
