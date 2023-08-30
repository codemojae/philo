/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 01:12:19 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 13:46:53 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	if (philo->have_l == 1 && *philo->can_r == 1)
	{
		*philo->can_r = 0;
		philo->have_r = 1;
		pthread_mutex_lock(philo->r_fork);
		print_msg(PICKING, philo);
	}
	else if (philo->have_r == 1 && *philo->can_l == 1)
	{
		*philo->can_l = 0;
		philo->have_l = 1;
		pthread_mutex_lock(philo->l_fork);
		print_msg(PICKING, philo);
	}
	else if (*philo->can_l == 1)
	{
		*philo->can_l = 0;
		philo->have_l = 1;
		pthread_mutex_lock(philo->l_fork);
		print_msg(PICKING, philo);
	}
	pthread_mutex_unlock(&lock);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	*philo->can_l = 1;
	philo->have_l = 0;
	pthread_mutex_unlock(philo->r_fork);
	*philo->can_r = 1;
	philo->have_r = 0;
}

void	sleeping(t_philo *philo)
{
	print_msg(SLEEPING, philo);
	usleep_ph(philo->data->t_sleep);
}

void	thinking(t_philo *philo)
{
	print_msg(THINKING, philo);
	while (philo->data->someone_dead == 0 && philo->data->finished == 0)
	{
		pickup_forks(philo);
		if (philo->have_l == 1 && philo->have_r == 1)
			return ;
	}
}

void	eating(t_philo *philo)
{
	philo->eat_count++;
	philo->last_meal = get_time();
	print_msg(EATING, philo);
	usleep_ph(philo->data->t_eat);
	drop_forks(philo);
	sleeping(philo);
}
