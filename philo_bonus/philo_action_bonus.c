/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 01:54:57 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 09:45:06 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lonely_philo(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_msg(PICKING, philo);
	while (philo->data->ending != 1)
	{
		usleep(420);
	}
	sem_post(philo->data->forks);
}

//monitoring에서 죽었는지 체크
int	philo_action(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &monitoring, philo))
		return (1);
	if (philo->id % 2 == 1)
		pickup_forks(philo);
	else
		sleep_ph(philo->data->t_eat);
	while (philo->data->philo_num != 1)
	{
		if (philo->eating)
			eating(philo);
		if (philo->eat_count == philo->data->eat_goal)
			exit (0);
		thinking(philo);
	}
	if (philo->data->philo_num == 1)
		lonely_philo(philo);
	return (0);
}
