/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 01:12:19 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/31 16:49:16 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_right_left(t_philo *philo)
{
	if (philo->get_r == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->get_r = 1;
		print_msg(PICKING, philo);
	}
	else if (philo->get_l == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->get_l = 1;
		print_msg(PICKING, philo);
	}
}

void	pick_left_right(t_philo *philo)
{
	if (philo->get_l == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->get_l = 1;
		print_msg(PICKING, philo);
	}
	else if (philo->get_r == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->get_r = 1;
		print_msg(PICKING, philo);
	}
}

void	pickup_forks(t_philo *philo)
{
	if (philo->pid % 2 == 1)
	{
		pick_right_left(philo);
	}
	else
	{
		pick_left_right(philo);
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
	usleep_ph(philo->data->t_eat);
	drop_forks(philo);
	print_msg(SLEEPING, philo);
	usleep_ph(philo->data->t_sleep);
	usleep(333);
}
