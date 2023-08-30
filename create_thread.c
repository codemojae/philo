/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:57:51 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 21:39:35 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_fin(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->edit);
	if (data->someone_dead == 1 || data->finished == 1)
		i = 1;
	pthread_mutex_unlock(&data->edit);
	return (i);
}

// 먹기 시작하면 즉시 last_meal을 바꿔야함.
void	*philo(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	pthread_mutex_lock(&philo->edit);
	philo->ttd = get_time() + philo->data->t_die;
	pthread_mutex_unlock(&philo->edit);
	while (1)
	{
		if (check_fin(philo->data))
			return (0);
		pickup_forks(philo);
		eating(philo);
		print_msg(THINKING, philo);
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
	if (data->eat_goal != -1)
	{
		if (pthread_create(&waiter, NULL, &waitering, data))
			return (error_philo("fail create thread"));
	}
	while (i < data->philo_num)
	{
		if (pthread_create(&data->thread[i], NULL, &philo, &data->philos[i]))
			return (error_philo("fail create thread"));
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitoring, data))
		return (error_philo("fail create thread"));
	pthread_join(waiter, NULL);
	pthread_join(monitor, NULL);
	join_thread(data);
	return (0);
}
