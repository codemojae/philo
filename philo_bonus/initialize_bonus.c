/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:53:26 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/23 12:05:15 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT, 0644, data->philo_num);
	if (!(data->forks))
		return (1);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	if (!(data->print))
		return (1);
	return (0);
}

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
	data->forks = NULL;
	data->print = NULL;
	if (init_sem(data))
		return (1);
	pthread_mutex_init(&data->edit, NULL);
	pthread_mutex_init(&data->start, NULL);
	return (0);
}

// pid는 fork()할때 사용, thread는 fork() 후 자식프로세스 모니터 만들때 사용, check은 보류.
int	init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].ttd = get_time() + data->t_die;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		i++;
	}
	return (0);
}

int	initialize(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv) == 1)
		return (1);
	if (init_philo(data) == 1)
		return (1);
	data->t_start = get_time();
	return (0);
}
