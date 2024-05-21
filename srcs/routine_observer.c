/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_observer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:31:50 by crea              #+#    #+#             */
/*   Updated: 2024/05/20 16:03:34 by crea             ###   ########.fr       */
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
		if (current_philo->current_meal == table->nbr_of_meals)
		{
			philo_has_eaten++;
			if (philo_has_eaten == table->nbr_of_philo)
			{
				table->dinner_end = true;
				pthread_mutex_lock(&table->is_writing);
				printf("All philo have eaten %d meals\n", table->nbr_of_meals);
				printf("Dinner have ended at %llu\n", get_time());
				pthread_mutex_unlock(&table->is_writing);
				break ;
			}
		}
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

	current_philo = table->philo;
	while (1)
	{
		current_time = get_time();
		if (current_philo->last_meal && (current_philo->is_eating == false) &&
			(current_time - current_philo->last_meal > table->philo->time_to_die))
		{
			pthread_mutex_lock(&table->death);
			if (!table->dinner_end)
			{
				current_philo->is_dead = true;
				pthread_mutex_lock(&table->is_writing);
				printf("%llu %d died\n", current_time, current_philo->index);
				table->dinner_end = true;
				printf("Dinner have ended at %llu\n", current_time);
				printf("Death check\n");
				pthread_mutex_unlock(&table->is_writing);
			}
			pthread_mutex_unlock(&table->death);
			return ;
		}
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
		usleep(1000);
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
	observer_action(table);
	return (NULL);
}
