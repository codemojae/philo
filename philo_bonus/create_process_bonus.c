/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:07:13 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 09:45:12 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_proc(t_data *data, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
	if (data->philo_num != philo_num)
		return (1);
	else
		return (0);
}

int	wait_child(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->philo_num)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			kill_proc(data, data->philo_num);
			return (2);
		}
		if ((status >> 8) == 1)
		{
			kill_proc(data, data->philo_num);
			return (1);
		}
		i++;
	}
	return (0);
}

// 각각의 프로세스가 철학자
// 각 프로세스의 스레드가 모니터
int	create_process(t_data *data)
{
	int	i;
	int	wait_code;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			return (kill_proc(data, i - 1));
		if (data->philos[i].pid == 0)
		{
			if (philo_action(&data->philos[i]) == 1)
				return (1);
			return (0);
		}
		i++;
	}
	wait_code = wait_child(data);
	if (wait_code == 1)
		return (0);
	else if (wait_code == 2)
		return (1);
	else
		print_msg(FULL, &data->philos[0]);
	return (0);
}
