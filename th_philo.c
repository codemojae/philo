/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:24:43 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/31 16:42:16 by hojakim          ###   ########.fr       */
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
	}
}

void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(PICKING, philo);
	while (!check_fin(philo->data))
	{
		usleep(100);
	}
	pthread_mutex_unlock(philo->r_fork);
}

// 먹기 시작하면 즉시 last_meal을 바꿔야함.
void	*philo(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	wait_for_start(philo);
	if (philo->pid % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->get_l = 1;
		print_msg(PICKING, philo);
		pthread_mutex_lock(philo->r_fork);
		philo->get_r = 1;
		print_msg(PICKING, philo);
	}
	usleep (10);
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
