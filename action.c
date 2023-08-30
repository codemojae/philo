/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 01:12:19 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 21:18:39 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	if (philo->pid % 2 == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(PICKING, philo);
		pthread_mutex_lock(philo->l_fork);
		print_msg(PICKING, philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_msg(PICKING, philo);
		pthread_mutex_lock(philo->r_fork);
		print_msg(PICKING, philo);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->edit);
	print_msg(EATING, philo);
	philo->eat_count++;
	philo->ttd = get_time() + philo->data->t_die;
	pthread_mutex_unlock(&philo->edit);
	usleep_ph(philo->data->t_eat);
	drop_forks(philo);
	print_msg(SLEEPING, philo);
	usleep_ph(philo->data->t_sleep);
}
