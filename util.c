/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 01:13:20 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 02:50:31 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//복붙
uint64_t	get_time(void)
{
	struct timeval	current_time;
	uint64_t		micro_seconds;

	gettimeofday(&current_time, NULL);
	micro_seconds = (current_time.tv_sec * (uint64_t)1000)
		+ (current_time.tv_usec / 1000);
	return (micro_seconds);
}

void	print_msg(int state, t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->t_start;
	if (state == EATING)
		printf("%lld   %d is eating %d\n", time, philo->pid, philo->eat_count);
	else if (state == SLEEPING)
		printf("%lld   %d is sleeping\n", time, philo->pid);
	else if (state == THINKING)
		printf("%lld   %d is thinking\n", time, philo->pid);
	else if (state == DEAD)
		printf("%lld   %d died\n", time, philo->pid);
	else if (state == PICKING)
		printf("%lld   %d has taken a fork\n", time, philo->pid);
	pthread_mutex_unlock(&philo->data->print);
}

int	usleep_ph(useconds_t time)
{
	uint64_t	start_sleep;

	start_sleep = get_time();
	while ((get_time() - start_sleep) < time)
		usleep(10); // 이건 조절
	return (0);
}
