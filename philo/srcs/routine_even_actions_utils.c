/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_even_actions_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:24:28 by crea              #+#    #+#             */
/*   Updated: 2024/05/22 21:46:39 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_first_meal_even_utils(t_table *table, t_philo *current_philo,
			long long current_time)
{
	long long	dinner_start;

	pthread_mutex_lock(&current_philo->dead_lock);
	pthread_mutex_lock(&table->is_writing);
	dinner_start = table->dinner_start;
	current_philo->is_dead = true;
	printf("%llu %d died\n", current_time - dinner_start, current_philo->index);
	printf("Dinner have ended at %llu\n", current_time - table->dinner_start);
	printf("Death at first meal check\n");
	table->dinner_end = true;
	pthread_mutex_unlock(&current_philo->dead_lock);
	pthread_mutex_unlock(&table->is_writing);
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
	pthread_mutex_lock(&current_philo->dead_lock);
	current_philo->last_meal = current_time;
	pthread_mutex_unlock(&current_philo->dead_lock);
	usleep(current_philo->time_to_eat * 1000);
	pthread_mutex_lock(&current_philo->dead_lock);
	if (table->nbr_of_meals != -1)
		current_philo->current_meal++;
	pthread_mutex_unlock(&current_philo->dead_lock);
	current_philo->first_meal = false;
	current_philo->is_eating = false;
	current_philo->is_sleeping = true;
}
