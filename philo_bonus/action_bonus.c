/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 23:22:04 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 02:31:40 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pickup_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_msg(PICKING, philo);
	sem_wait(philo->data->forks);
	print_msg(PICKING, philo);
	philo->eating = 1;
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	eating(t_philo *philo)
{
	print_msg(EATING, philo);
	philo->eat_count++;
	philo->ttd = get_time() + philo->data->t_die;
	sleep_ph(philo->data->t_eat);
	drop_forks(philo);
	philo->eating = 0;
	if (philo->eat_count < philo->data->eat_goal || philo->data->eat_goal == -1)
		sleeping(philo);
}

void	sleeping(t_philo *philo)
{
	print_msg(SLEEPING, philo);
	sleep_ph(philo->data->t_sleep);
}

void	thinking(t_philo *philo)
{
	print_msg(THINKING, philo);
	pickup_forks(philo);
}
