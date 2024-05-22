/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_observer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:31:50 by crea              #+#    #+#             */
/*   Updated: 2024/05/22 21:53:37 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	check_meals(t_table *table)
{
	int		philo_has_eaten;
	t_philo	*current_philo;

	philo_has_eaten = 0;
	current_philo = table->philo;
	while (1)
	{
		pthread_mutex_lock(&current_philo->dead_lock);
		if (current_philo->current_meal == table->nbr_of_meals)
		{
			philo_has_eaten++;
			if (philo_has_eaten == table->nbr_of_philo)
			{
				pthread_mutex_unlock(&current_philo->dead_lock);
				check_meals_utils(table);
				return ;
			}
		}
		pthread_mutex_unlock(&current_philo->dead_lock);
		current_philo = current_philo->next;
		if (current_philo == table->philo)
			break ;
	}
	return ;
}

static void	check_death(t_table *table)
{
	t_philo		*current_philo;
	long long	current_time;
	long long	time_to_die;

	current_philo = table->philo;
	time_to_die = current_philo->time_to_die;
	while (1)
	{
		current_time = get_time();
		pthread_mutex_lock(&current_philo->dead_lock);
		if (current_philo->last_meal
			&& (current_time - current_philo->last_meal >= time_to_die))
		{
			pthread_mutex_unlock(&current_philo->dead_lock);
			check_death_utils(table, current_philo, current_time);
			return ;
		}
		pthread_mutex_unlock(&current_philo->dead_lock);
		current_philo = current_philo->next;
		if (current_philo == table->philo)
			break ;
	}
	return ;
}

static void	observer_action(t_table *table)
{
	while (!table->dinner_end)
	{
		if (table->nbr_of_meals != -1)
			check_meals(table);
		if (table->dinner_end)
			break ;
		check_death(table);
	}
	return ;
}

void	*observer(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	(void)table;
	pthread_mutex_lock(&table->is_writing);
	printf("Observer routine has started\n");
	pthread_mutex_unlock(&table->is_writing);
	if (table->nbr_of_philo != 1)
		observer_action(table);
	return (NULL);
}
