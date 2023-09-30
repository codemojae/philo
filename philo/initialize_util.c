/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 02:01:12 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 02:02:28 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data->im_full = 0;
	data->ending = 0;
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

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
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->forks[i] = 0;
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork_m = &data->fork_m[i];
		data->philos[i].r_fork_m = &data->fork_m[(i + 1) % data->philo_num];
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->philos[i].edit, NULL))
			return (-1);
		if (pthread_mutex_init(&data->fork_m[i], NULL))
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&data->edit, NULL))
		return (-1);
	if (pthread_mutex_init(&data->print, NULL))
		return (-1);
	if (pthread_mutex_init(&data->start, NULL))
		return (-1);
	return (0);
}

int	init_malloc(t_data *data, int philo_num)
{	
	data->thread = malloc(sizeof(pthread_t) * philo_num);
	if (!data->thread)
		return (error_philo("data malloc"));
	data->philos = malloc(sizeof(t_philo) * philo_num);
	if (!data->philos)
		return (error_philo("philo malloc"));
	data->fork_m = malloc(sizeof(pthread_mutex_t) * philo_num);
	if (!data->fork_m)
		return (error_philo("fork malloc"));
	data->forks = malloc(sizeof(int) * philo_num);
	if (!data->forks)
		return (error_philo("fork malloc"));
	return (0);
}
