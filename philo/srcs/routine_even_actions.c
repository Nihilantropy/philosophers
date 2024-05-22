/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_even_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:45 by crea              #+#    #+#             */
/*   Updated: 2024/05/22 22:14:08 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_first_meal(t_table *table, t_philo *current_philo)
{
	long long	current_time;

	if (current_philo->first_meal && current_philo->index % 2 == 0)
	{
		current_time = get_time();
		if (current_time - table->dinner_start >= current_philo->time_to_die)
		{
			pthread_mutex_lock(&table->death);
			if (table->dinner_end)
			{
				pthread_mutex_unlock(&table->death);
				return (0);
			}
			check_first_meal_even_utils(table, current_philo, current_time);
			pthread_mutex_unlock(&table->death);
			return (0);
		}
	}
	return (1);
}

void	eating_even(t_table *table, t_philo *current_philo)
{
	if (!table || !current_philo)
		return ;
	pthread_mutex_lock(&current_philo->right_fork);
	pthread_mutex_lock(&current_philo->next->right_fork);
	if (!check_first_meal(table, current_philo))
	{
		pthread_mutex_unlock(&current_philo->right_fork);
		pthread_mutex_unlock(&current_philo->next->right_fork);
		return ;
	}
	pthread_mutex_lock(&table->is_writing);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_writing);
		pthread_mutex_unlock(&current_philo->right_fork);
		pthread_mutex_unlock(&current_philo->next->right_fork);
		return ;
	}
	eating_even_utils(table, current_philo);
	pthread_mutex_unlock(&current_philo->right_fork);
	pthread_mutex_unlock(&current_philo->next->right_fork);
}

void	sleeping_even(t_table *table, t_philo *current_philo)
{
	long long	current_time;
	long long	dinner_start;
	int			index;

	if (table->dinner_end)
		return ;
	pthread_mutex_lock(&table->is_writing);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_writing);
		return ;
	}
	current_time = get_time();
	dinner_start = table->dinner_start;
	index = current_philo->index;
	printf("%llu %d is sleeping\n", current_time - dinner_start, index);
	pthread_mutex_unlock(&table->is_writing);
	usleep(current_philo->time_to_sleep * 1000);
	current_philo->is_sleeping = false;
	current_philo->is_thinking = true;
}

void	thinking_even(t_table *table, t_philo *current_philo)
{
	long long	current_time;
	long long	dinner_start;
	int			index;

	pthread_mutex_lock(&table->is_writing);
	if (table->dinner_end)
	{
		pthread_mutex_unlock(&table->is_writing);
		return ;
	}
	current_time = get_time();
	dinner_start = table->dinner_start;
	index = current_philo->index;
	printf("%llu %d is thinking\n", current_time - dinner_start, index);
	pthread_mutex_unlock(&table->is_writing);
	current_philo->is_thinking = false;
	current_philo->is_eating = true;
}
