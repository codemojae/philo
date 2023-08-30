/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 01:13:20 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 17:40:05 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//복붙
uint64_t	get_time(void)
{
	struct timeval	current_time;
	uint64_t		micro_seconds;

	if (gettimeofday(&current_time, NULL))
		return (error_philo("fail gettimeofday"));
	micro_seconds = (current_time.tv_sec * (uint64_t)1000)
		+ (current_time.tv_usec / 1000);
	return (micro_seconds);
}

void	print_msg(int state, t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->t_start;
	if (philo->data->someone_dead == 0 && philo->data->finished == 0)
	{
		if (state == EATING)
			printf("%lld %d %sis eating%s\n", time, philo->pid, GREEN, RESET);
		else if (state == SLEEPING)
			printf("%lld %d %sis sleeping%s\n", time, philo->pid, YELLOW, RESET);
		else if (state == THINKING)
			printf("%lld %d is thinking\n", time, philo->pid);
		else if (state == DEAD)
			printf("%lld %d %sdied%s\n", time, philo->pid, RED, RESET);
		else if (state == PICKING)
			printf("%lld %d has taken a fork\n", time, philo->pid);
		else if (state == FULL)
			printf("%lld ALL the philosophers finished meal\n", time);
	}
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
