/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:57:51 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 13:47:44 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 먹기 시작하면 즉시 last_meal을 바꿔야함.
void	*philo(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->pid % 2 == 0)
	{
		printf("even");
		pthread_mutex_lock(philo->l_fork);
		*philo->can_l = 0;
		philo->have_l = 1;
		print_msg(PICKING, philo);
		pthread_mutex_lock(philo->r_fork);
		*philo->can_r = 0;
		philo->have_r = 1;
		eating(philo);
	}
	usleep_ph(1);
	while (philo->data->someone_dead == 0 && philo->data->finished == 0)
	{
		pickup_forks(philo);
		if (philo->have_l == 1 && philo->have_r == 1)
			eating(philo);
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
	while (data->someone_dead == 0 && data->finished == 0)
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (get_time() - data->philos[i].last_meal > data->t_die)
			{
				printf("that's why DEAD");
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
	while (data->someone_dead == 0 && data->finished == 0)
	{
		if (data->im_full == data->philo_num)
		{
				printf("that's why FULL");
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
		//if (pthread_detach(data->thread[i]))
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
	if (pthread_create(&monitor, NULL, &monitoring, data))
		return (error_philo("fail create thread"));
	while (i < data->philo_num)
	{
		if (pthread_create(&data->thread[i], NULL, &philo, &data->philos[i]))
			return (error_philo("fail create thread"));
		i++;
		//usleep_ph(1);
	}
	if (data->eat_goal != -1)
	{
		if (pthread_create(&waiter, NULL, &waitering, data))
			return (error_philo("fail create thread"));
		pthread_join(waiter, NULL);
	}
	pthread_join(monitor, NULL);
	join_thread(data);
	return (0);
}
