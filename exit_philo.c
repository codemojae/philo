/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:12:57 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/31 16:27:17 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].edit);
		i++;
	}
	pthread_mutex_destroy(&data->edit);
	pthread_mutex_destroy(&data->print);
}

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	if (data->thread)
		free(data->thread);
}

int	exit_philo(t_data *data)
{
	free_thread(data);
	free_data(data);
	return (1);
}
