/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_odd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:31:11 by crea              #+#    #+#             */
/*   Updated: 2024/05/20 16:26:18 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	philo_actions_odd(t_table *table, t_philo *current_philo)
{
	if (!table || !current_philo)
		return ;
	while (1)
	{
		if (table->dinner_end)
			break ;
		if (current_philo->is_eating)
			eating_odd(table, current_philo);
		if (current_philo->is_sleeping)
			sleeping_odd(table, current_philo);
		if (current_philo->is_thinking)
			thinking_odd(table, current_philo);
	}
	return ;
}

static int	check_if_one(t_table *table, t_philo *current_philo)
{
	if (table->nbr_of_philo == 1)
	{
		pthread_mutex_lock(&table->death);
		pthread_mutex_lock(&table->is_writing);
		usleep(current_philo->time_to_die * 1000);
		current_philo->is_dead = true;
		printf("%llu %d died\n", get_time(), current_philo->index);
		printf("dinner ended at %llu\n", get_time());
		printf("Death cause: loneliness :(\n");
		table->dinner_end = true;
		pthread_mutex_unlock(&table->is_writing);
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	return (0);
}

void	*philo_routine_odd(void *arg)
{
	t_table *table;
	t_philo *current_philo;

	table = (t_table *)arg;
	if (!table)
		return (NULL);
	pthread_mutex_lock(&table->is_sitting);
	current_philo = table->philo;
	while ((current_philo->index) != table->philo_index + 1)
		current_philo = current_philo->next;
	table->philo_index++;
	if (current_philo->index % 2 != 0 && 
		current_philo->index != table->nbr_of_philo)
		current_philo->is_eating = true;
	else
		current_philo->is_thinking = true;
	if (current_philo->index == 1)
	{
		pthread_mutex_lock(&table->is_writing);
		table->dinner_start = get_time();
		printf("dinner started at %llu\n", table->dinner_start);
		pthread_mutex_unlock(&table->is_writing);
	}
	pthread_mutex_unlock(&table->is_sitting);
	if (check_if_one(table, current_philo))
		return (NULL);
	philo_actions_odd(table, current_philo);
	return (NULL);
}
