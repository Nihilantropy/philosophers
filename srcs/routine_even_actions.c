/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_even_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:45 by crea              #+#    #+#             */
/*   Updated: 2024/05/20 17:27:30 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_first_meal(t_table *table, t_philo *current_philo)
{
	long long current_time;

	if (current_philo->first_meal && current_philo->index % 2 == 0)
	{
		pthread_mutex_lock(&table->death);
		current_time = get_time();
		if (current_time - table->dinner_start > current_philo->time_to_die)
		{
			current_philo->is_dead = true;
			pthread_mutex_lock(&table->is_writing);
			printf("%llu %d died\n", current_time, current_philo->index);
			printf("Dinner have ended at %llu\n", current_time);
			printf("Death at first meal check\n");
			pthread_mutex_unlock(&table->is_writing);
			table->dinner_end = true;
			pthread_mutex_unlock(&table->death);
			return (0);
		}
		pthread_mutex_unlock(&table->death);
	}
	return (1);
}

void	eating_even(t_table *table, t_philo *current_philo)
{
	long long current_time;

	if (!table || !current_philo)
		return ;
	pthread_mutex_lock(&current_philo->right_fork);
	pthread_mutex_lock(&current_philo->next->right_fork);
	pthread_mutex_lock(&current_philo->dead_lock);
	
	if (!check_first_meal(table, current_philo))
	{
		pthread_mutex_unlock(&current_philo->right_fork);
		pthread_mutex_unlock(&current_philo->next->right_fork);
		pthread_mutex_unlock(&current_philo->dead_lock);
		return ;
	}
	current_time = get_time();
	if (!table->dinner_end)
	{
		pthread_mutex_lock(&table->is_writing);
		printf("%llu %d has taken a fork\n", current_time, current_philo->index);
		printf("%llu %d is eating\n", current_time, current_philo->index);
		pthread_mutex_unlock(&table->is_writing);
	}

	usleep(current_philo->time_to_eat * 1000);
	current_philo->last_meal = get_time();

	if (table->nbr_of_meals != -1)
		current_philo->current_meal++;
	current_philo->first_meal = false;
	current_philo->is_eating = false;
	current_philo->is_sleeping = true;

	pthread_mutex_unlock(&current_philo->right_fork);
	pthread_mutex_unlock(&current_philo->next->right_fork);
	pthread_mutex_unlock(&current_philo->dead_lock);

}

void	sleeping_even(t_table *table, t_philo *current_philo)
{
	long long current_time;

	if (table->dinner_end)
		return ;
	current_time = get_time();
	pthread_mutex_lock(&table->is_writing);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_writing);
		return ;
	}
	else
		printf("%llu %d is sleeping\n", current_time, current_philo->index);
	pthread_mutex_unlock(&table->is_writing);
	usleep(current_philo->time_to_sleep * 1000);
	
	current_philo->is_sleeping = false;
	current_philo->is_thinking = true;
}

void	thinking_even(t_table *table, t_philo *current_philo)
{
	long long current_time;

	if (table->dinner_end)
		return;
	current_time = get_time();
	pthread_mutex_lock(&table->is_writing);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_writing);
		return ;
	}
	else
		printf("%llu %d is thinking\n", current_time, current_philo->index);
	pthread_mutex_unlock(&table->is_writing);
	usleep(1000);
	current_philo->is_thinking = false;
	current_philo->is_eating = true;
}