/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:07:13 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/26 00:58:15 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_for_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start);
	//pthread_mutex_lock(&philo->edit);
	philo->ttd = philo->data->t_start + philo->data->t_die;
	//pthread_mutex_unlock(&philo->edit);
	pthread_mutex_unlock(&philo->data->start);
}

void	lonely_philo(t_philo *philo)
{
	sem_wait("forks");
	print_msg(PICKING, philo);
	while (!check_fin(philo->data))
	{
		usleep(333);
	}
	sem_post("forks");
}

//monitoring에서 죽었는지 체크
int	philo_action(t_philo *philo)
{
	if (pthread_create(philo->thread, NULL, &monitoring, philo))
		return (1);
	wait_for_start(philo);
	if (philo->id % 2 == 0)
		pickup_forks(philo);
	else
		usleep(philo->data->philo_num * 40);
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

// 각각의 프로세스가 철학자
// 각 프로세스의 스레드가 모니터 
int	create_process(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->philo_num)
	{
		data->philos[i].pid = fork();
		// 자식프로세스에서 실행
		if (data->philos[i].pid == 0)
		{
			// 오류처리?
			philo_action(&data->philos[i]);
			return (0);
		}
		i++;
	}
	data->t_start = get_time();
	pthread_mutex_unlock(&data->start);
	i = 0;
	while (i < data->philo_num)
	{
		waitpid(-1, &status, 0);
		if ((status >> 8) == 1) // 죽음
		{
			kill_all_proc(data);
			return (0);
		}
		i++;
	}
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
