/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 23:22:04 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/25 23:22:25 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pickup_forks(t_philo *philo)
{
	sem_wait("forks");
	print_msg(PICKING, philo);
	sem_wait("forks");
	print_msg(PICKING, philo);
	philo->eating = 1;
}

void	drop_forks(t_philo *philo)
{
	sem_post("forks");
	sem_post("forks");
	philo->eating = 0;
}

void	eating(t_philo *philo)
{
	print_msg(EATING, philo);
	philo->eat_count++;
	philo->ttd = get_time() + philo->data->t_die;
	sleep_ph(philo->data->t_eat);
	drop_forks(philo);
	print_msg(SLEEPING, philo);
	sleep_ph(philo->data->t_sleep);
	usleep(333);
}

void	thinking(t_philo *philo)
{
	print_msg(THINKING, philo);
	pickup_forks(philo);
}
