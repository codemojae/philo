/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:44:45 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/22 22:23:38 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	if (philo->get_l == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->get_l = 1;
		print_msg(PICKING, philo);
	}
	if (philo->get_r == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->get_r = 1;
		print_msg(PICKING, philo);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	philo->get_l = 0;
	pthread_mutex_unlock(philo->r_fork);
	philo->get_r = 0;
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->edit);
	print_msg(EATING, philo);
	philo->eat_count++;
	philo->ttd = get_time() + philo->data->t_die;
	pthread_mutex_unlock(&philo->edit);
	sleep_ph(philo->data->t_eat);
	drop_forks(philo);
	print_msg(SLEEPING, philo);
	sleep_ph(philo->data->t_sleep);
	usleep(333);
}
