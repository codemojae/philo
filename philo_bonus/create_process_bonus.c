/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:07:13 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/26 15:12:18 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lonely_philo(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_msg(PICKING, philo);
	while (philo->data->ending != 1)
	{
		usleep(333);
	}
	sem_post(philo->data->forks);
}

//monitoring에서 죽었는지 체크
int	philo_action(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &monitoring, philo))
		return (1);
	if (philo->id % 2 == 1)
		pickup_forks(philo);
	else
		sleep_ph(philo->data->t_eat);
	while (philo->data->philo_num != 1)
	{
		if (philo->eating)
			eating(philo);
		if (philo->eat_count == philo->data->eat_goal)
			exit (0);
		thinking(philo);
	}
	if (philo->data->philo_num == 1)
		lonely_philo(philo);
	return (0);
}

void	kill_all_proc(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

// 각각의 프로세스가 철학자
// 각 프로세스의 스레드가 모니터
int	create_process(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			if (philo_action(&data->philos[i]) == 1)
				return (1);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		waitpid(-1, &status, 0);
		if ((status >> 8) == 1)
		{
			kill_all_proc(data);
			return (0);
		}
		i++;
	}
	print_msg(FULL, &data->philos[0]);
	return (0);
}
