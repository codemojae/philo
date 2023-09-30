/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:44:57 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 00:55:59 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->fork_m[i]);
		pthread_mutex_destroy(&data->philos[i].edit);
		i++;
	}
	pthread_mutex_destroy(&data->edit);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->start);
}

void	free_data(t_data *data)
{
	if (data->fork_m)
		free(data->fork_m);
	if (data->philos)
		free(data->philos);
	if (data->thread)
		free(data->thread);
	if (data->forks)
		free(data->forks);
}

int	exit_philo(t_data *data)
{
	free_mutex(data);
	free_data(data);
	return (1);
}
