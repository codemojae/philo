/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:45:30 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 02:09:50 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_stat(t_philo *philo)
{
	pthread_mutex_lock(&philo->edit);
	if (get_time() > philo->ttd)
	{
		print_msg(DEAD, philo);
		pthread_mutex_lock(&philo->data->edit);
		philo->data->ending = 1;
		pthread_mutex_unlock(&philo->data->edit);
	}
	if (philo->eat_count >= philo->data->eat_goal && philo->check == 0)
	{
		pthread_mutex_lock(&philo->data->edit);
		philo->data->im_full++;
		pthread_mutex_unlock(&philo->data->edit);
		philo->check = 1;
	}
	pthread_mutex_unlock(&philo->edit);
}

void	*monitoring(void *dat)
{
	t_data		*data;
	int			i;

	data = (t_data *) dat;
	while (!check_fin(data))
	{
		i = 0;
		while (i < data->philo_num)
		{
			check_philo_stat(&data->philos[i]);
			i++;
		}
		usleep(500);
	}
	return (0);
}
