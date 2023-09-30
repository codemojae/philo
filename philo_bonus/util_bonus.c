/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:46:02 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 02:43:29 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

uint64_t	get_time(void)
{
	struct timeval	current_time;
	uint64_t		micro_sec;

	if (gettimeofday(&current_time, NULL))
		return (error_philo("fail gettimeofday"));
	micro_sec = (current_time.tv_sec * (uint64_t)1000)
		+ (current_time.tv_usec / 1000);
	return (micro_sec);
}

void	print_msg(int state, t_philo *philo)
{
	uint64_t	time;

	sem_wait(philo->data->print);
	sem_wait(philo->data->dead);
	time = get_time() - philo->data->t_start;
	if (philo->data->ending != 1)
	{
		if (state == EATING)
			printf("%lld %d %sis eating%s\n", time, philo->id, GREEN, RESET);
		else if (state == SLEEPING)
			printf("%lld %d %sis sleeping%s\n", time, philo->id, YELLOW, RESET);
		else if (state == THINKING)
			printf("%lld %d is thinking\n", time, philo->id);
		else if (state == DEAD)
			printf("%lld %d %sdied%s\n", time, philo->id, RED, RESET);
		else if (state == PICKING)
			printf("%lld %d has taken a fork\n", time, philo->id);
		else if (state == FULL)
			printf("**** ALL the philosophers had a meal enough ****\n");
	}
	sem_post(philo->data->dead);
	sem_post(philo->data->print);
}

int	sleep_ph(useconds_t time)
{
	uint64_t	start_sleep;

	start_sleep = get_time();
	while (get_time() - start_sleep < time)
	{
		usleep(250);
	}
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
