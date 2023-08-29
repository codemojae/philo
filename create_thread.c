/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:57:51 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 02:44:15 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 먹기 시작하면 즉시 last_meal을 바꿔야함.
void	*philo(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	while (!philo->data->someone_dead && !philo->data->finished)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}

// time 을 get_time() - data->philos[i].last_meal 로 함.
void	*monitoring(void *dat)
{
	t_data		*data;
	int			i;

	data = (t_data *) dat;
	while (!data->someone_dead && !data->finished)
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (get_time() - data->philos[i].last_meal > data->t_die)
			{
				print_msg(DEAD, &data->philos[i]);
				data->someone_dead = 1;
			}
			if (data->philos[i].eat_count == data->eat_goal
				&& data->philos[i].check == 0)
			{
				pthread_mutex_lock(&data->edit);
				data->im_full++;
				data->philos[i].check = 1;
				pthread_mutex_unlock(&data->edit);
			}
			i++;
		}
	}
	return (0);
}

void	*waitering(void *dat)
{
	t_data	*data;

	data = (t_data *) dat;
	while (!data->someone_dead && !data->finished)
	{
		if (data->im_full == data->eat_goal)
		{
			pthread_mutex_lock(&data->edit);
			data->finished = 1;
			pthread_mutex_unlock(&data->edit);
		}
	}
	return (0);
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
	}
	return (0);
}

int	create_thread(t_data *data)
{
	pthread_t	monitor;
	pthread_t	waiter;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, &data))
		return (error_philo("fail create thread"));
	while (i < data->philo_num)
	{
		if (pthread_create(&data->thread[i], NULL, &philo, &data->philos[i]))
			return (error_philo("fail create thread"));
		i++;
		//sleep 필요?
	}
	if (data->eat_goal != -1)
	{
		if (pthread_create(&waiter, NULL, &waitering, &data))
			return (error_philo("fail create thread"));
		pthread_join(waiter, NULL);
	}
	join_thread(data);
	pthread_join(monitor, NULL);
	return (0);
}
