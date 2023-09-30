/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:44:45 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 02:08:51 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	if (philo->get_l == 0)
	{
		pthread_mutex_lock(philo->l_fork_m);
		philo->get_l = 1;
		philo->data->forks[philo->pid] = 1;
		print_msg(PICKING, philo);
	}
	else if (philo->get_r == 0)
	{
		pthread_mutex_lock(philo->r_fork_m);
		philo->get_r = 1;
		philo->data->forks[(philo->pid + 1) % philo->data->philo_num] = 1;
		print_msg(PICKING, philo);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->get_l)
	{
		philo->get_l = 0;
		philo->data->forks[philo->pid] = 0;
		pthread_mutex_unlock(philo->l_fork_m);
	}
	if (philo->get_r)
	{
		philo->get_r = 0;
		philo->data->forks[(philo->pid + 1) % philo->data->philo_num] = 0;
		pthread_mutex_unlock(philo->r_fork_m);
	}
}

void	eating(t_philo *philo)
{
	print_msg(EATING, philo);
	pthread_mutex_lock(&philo->edit);
	philo->eat_count++;
	philo->ttd = get_time() + philo->data->t_die;
	pthread_mutex_unlock(&philo->edit);
	sleep_ph(philo->data->t_eat);
	drop_forks(philo);
	print_msg(SLEEPING, philo);
	sleep_ph(philo->data->t_sleep);
	usleep(500);
}
