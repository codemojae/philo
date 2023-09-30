/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 23:25:10 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 02:41:40 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// 배부른건 waitering에서 가져옴.
void	*monitoring(void *dat)
{
	t_philo	*philo;

	philo = (t_philo *) dat;
	while (philo->data->ending != 1)
	{
		if (get_time() > philo->ttd)
		{
			print_msg(DEAD, philo);
			sem_wait(philo->data->dead);
			philo->data->ending = 1;
			break ;
		}
		usleep(200);
	}
	exit(1);
}
