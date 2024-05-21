/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:05:50 by crea              #+#    #+#             */
/*   Updated: 2024/05/20 02:40:27 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define ERR_NBR_ARG "ERROR! Wrong nbr of arguments. Try with 5 or 6 args.\n"
# define ERR_ARG_FORM "ERROR! Wrong argument format. Try with just numbers.\n"
# define ERR_ZERO_INPUT "ERROR! Argument value can't be zero or >= INT_MAX.\n"
# define ERR_MAX_THREAD "ERROR! nbr of philo is too high. Invite less philo.\n"
# define ERR_THREAD_ALLOC "ERROR! Can't allocate memory for the threads.\n"
# define ERR_PHILO_THREAD_CREATE "ERROR! Can't create philo thread.\n"
# define ERR_OBS_THREAD_CREATE "ERROR! Can't create observer thread.\n"
# define ERR_THREAD_JOIN "ERROR! Can't join threads.\n"
# define ERR_PHILO_MUTEX "can't init philo mutexes\n"
# define ERR_PHILO_ALLOC "can't alloc mem for philo\n"
# define ERR_INIT_PHILO "can't init new philo\n"

# define CHECK_PASSED "Check passed!\n"
# define TABLE_READY "Table is ready!\n"
# define PHILO_LIST_READY "Philosophers list is ready!\n"

#endif