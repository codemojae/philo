/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:45:55 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/25 20:48:07 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_lock(&philo->edit);
	philo->ttd = philo->data->t_start + philo->data->t_die;
	pthread_mutex_unlock(&philo->edit);
	pthread_mutex_unlock(&philo->data->start);
}

void	thinking(t_philo *philo)
{
	print_msg(THINKING, philo);
	while (philo->get_l == 0 || philo->get_r == 0)
	{
		if (check_fin(philo->data))
			return ;
		pickup_forks(philo);
		usleep(100);
	}
}

void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(PICKING, philo);
	while (!check_fin(philo->data))
	{
		usleep(333);
	}
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	wait_for_start(philo);
	if (philo->pid % 2 == 0)
		pickup_forks(philo);
	else
		usleep(philo->data->philo_num * 40);
	while (!check_fin(philo->data) && philo->data->philo_num != 1)
	{
		if (philo->get_r == 1 && philo->get_l == 1)
			eating(philo);
		thinking(philo);
	}
	if (philo->data->philo_num == 1)
		lonely_philo(philo);
	return (0);
}
