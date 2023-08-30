/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:56:32 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 12:18:41 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_ph(const char *str)
{
	long long	result;
	int			pm;
	int			return_value;

	result = 0;
	pm = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			pm = pm * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result < -2147483648 || result > 2147483647)
			printf("over int\n");
		str++;
	}
	if (result != 0)
		result *= pm;
	return_value = result;
	return (return_value);
}

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
	data->someone_dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->edit, NULL);
	pthread_mutex_init(&data->print, NULL);
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
		data->philos[i].last_meal = get_time();
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		data->philos[i].check = 0;
		data->philos[i].have_l = 0;
		data->philos[i].have_r = 0;
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

int	init_can(t_data *data)
{
	int	i;

	data->can = malloc(sizeof(int) * data->philo_num);
	if (!data->forks)
		return (error_philo("can malloc"));
	i = 0;
	while (i < data->philo_num)
	{
		data->can[i] = 1;
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].can_l = &data->can[i];
		data->philos[i].can_r = &data->can[(i + 1) % data->philo_num];
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
	if (init_can(data) == -1)
		return (-1);
	data->t_start = get_time();
	return (0);
}
