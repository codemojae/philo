/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:56:32 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/31 16:27:23 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 데이터 초기화
	// 범위설정이 필요한가?
	// 범위설정이 필요한가?
	// 범위설정이 필요한가?
int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_num = ft_atoi_ph(argv[1]);
	data->t_die = (uint64_t) ft_atoi_ph(argv[2]);
	data->t_eat = (uint64_t) ft_atoi_ph(argv[3]);
	data->t_sleep = (uint64_t) ft_atoi_ph(argv[4]);
	if (argc == 6)
		data->eat_goal = ft_atoi_ph(argv[5]);
	else
		data->eat_goal = -1;
	data->thread = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->thread)
		return (error_philo("data malloc"));
	data->im_full = 0;
	data->ending = 0;
	pthread_mutex_init(&data->edit, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->start, NULL);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (error_philo("philo malloc"));
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].pid = i + 1;
		data->philos[i].ttd = get_time() + data->t_die;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		data->philos[i].check = 0;
		data->philos[i].get_r = 0;
		data->philos[i].get_l = 0;
		pthread_mutex_init(&data->philos[i].edit, NULL);
		i++;
	}
	return (0);
}

int	init_fork(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (error_philo("fork malloc"));
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_num];
		i++;
	}
	return (0);
}

int	initialize(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv) == -1)
		return (-1);
	if (init_philo(data) == -1)
		return (-1);
	if (init_fork(data) == -1)
		return (-1);
	data->t_start = get_time();
	return (0);
}
