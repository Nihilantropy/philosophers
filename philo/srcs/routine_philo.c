/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:31:11 by crea              #+#    #+#             */
/*   Updated: 2024/05/23 17:06:39 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	philo_actions(t_table *table, t_philo *current_philo)
{
	if (!table || !current_philo)
		return ;
	while (1)
	{
		if (table->dinner_end)
		{
			break ;
		}
		pthread_mutex_unlock(&table->death);
		if (current_philo->is_eating)
			eating(table, current_philo);
		if (current_philo->is_sleeping)
			sleeping(table, current_philo);
		if (current_philo->is_thinking)
			thinking(table, current_philo);
	}
	return ;
}

static int	check_if_one(t_table *table, t_philo *current_philo)
{
	long long	dinner_start;

	pthread_mutex_lock(&table->death);
	if (table->nbr_of_philo == 1)
	{
		pthread_mutex_lock(&table->is_writing);
		usleep(current_philo->time_to_die * 1000);
		current_philo->is_dead = true;
		dinner_start = table->dinner_start;
		printf("%llu 1 died\n", get_time() - dinner_start);
		printf("dinner ended at %llu\n", get_time() - table->dinner_start);
		printf("Death cause: loneliness :(\n");
		table->dinner_end = true;
		pthread_mutex_unlock(&table->is_writing);
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	pthread_mutex_unlock(&table->death);
	return (0);
}

static void	philo_routine_utils(t_table *table)
{
	long long	dinner_start;

	pthread_mutex_lock(&table->is_writing);
	table->dinner_start = get_time();
	dinner_start = table->dinner_start;
	printf("dinner started at %llu\n", dinner_start - dinner_start);
	pthread_mutex_unlock(&table->is_writing);
}

void	*philo_routine(void *arg)
{
	t_table	*table;
	t_philo	*current_philo;

	table = (t_table *)arg;
	if (!table)
		return (NULL);
	pthread_mutex_lock(&table->is_sitting);
	current_philo = table->philo;
	while ((current_philo->index) != table->philo_index + 1)
		current_philo = current_philo->next;
	table->philo_index++;
	if ((current_philo->index % 2 != 0)
		&& (current_philo->index != table->nbr_of_philo))
		current_philo->is_eating = true;
	else
		current_philo->is_thinking = true;
	if (current_philo->index == 1)
		philo_routine_utils(table);
	pthread_mutex_unlock(&table->is_sitting);
	if (check_if_one(table, current_philo))
		return (NULL);
	philo_actions(table, current_philo);
	return (NULL);
}
