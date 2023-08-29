/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 01:12:19 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 02:37:31 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(PICKING, philo);
	pthread_mutex_lock(philo->l_fork);
	print_msg(PICKING, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	print_msg(SLEEPING, philo);
	usleep_ph(philo->data->t_sleep);
}

void	thinking(t_philo *philo)
{
	print_msg(THINKING, philo);
}

void	eating(t_philo *philo)
{
	pickup_forks(philo);
	// philo에 락이 필요한가?
	print_msg(EATING, philo);
	philo->eat_count++;
	philo->last_meal = get_time();
	usleep_ph(philo->data->t_eat);
	drop_forks(philo);
}
