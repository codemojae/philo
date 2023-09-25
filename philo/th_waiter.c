/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_waiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:45:59 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/31 17:45:59 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->edit);
	if (data->im_full == data->philo_num)
		i = 1;
	pthread_mutex_unlock(&data->edit);
	return (i);
}

void	*waitering(void *dat)
{
	t_data	*data;

	data = (t_data *) dat;
	while (!check_fin(data))
	{
		if (check_full(data))
		{
			print_msg(FULL, &data->philos[0]);
			pthread_mutex_lock(&data->edit);
			data->ending = 2;
			pthread_mutex_unlock(&data->edit);
		}
	}
	return (0);
}
