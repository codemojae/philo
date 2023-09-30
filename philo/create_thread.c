/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:44:38 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 01:05:01 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_fin(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->edit);
	if (data->ending != 0)
		i = data->ending;
	pthread_mutex_unlock(&data->edit);
	return (i);
}

int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->thread[i], NULL))
			return (error_philo("fail join thread"));
		i++;
		usleep(10);
	}
	return (0);
}

int	create_thread(t_data *data)
{
	pthread_t	monitor;
	pthread_t	waiter;
	int			i;

	i = -1;
	if (data->eat_goal != -1)
	{
		if (pthread_create(&waiter, NULL, &waitering, data))
			return (error_philo("fail create thread"));
	}
	pthread_mutex_lock(&data->start);
	while (++i < data->philo_num)
	{	
		if (pthread_create(&data->thread[i], NULL, &philo, &data->philos[i]))
			return (error_philo("fail create thread"));
	}
	data->t_start = get_time();
	pthread_mutex_unlock(&data->start);
	if (pthread_create(&monitor, NULL, &monitoring, data))
		return (error_philo("fail create thread"));
	join_thread(data);
	if (data->eat_goal != -1)
		pthread_join(waiter, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
