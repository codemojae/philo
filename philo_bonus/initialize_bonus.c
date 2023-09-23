/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:53:26 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/23 08:53:47 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	data->ending = 0;
	pthread_mutex_init(&data->edit, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->start, NULL);
	return (0);
}