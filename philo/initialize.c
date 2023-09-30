/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:45:03 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 02:02:02 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize(t_data *data, int argc, char **argv)
{
	if (init_malloc(data, ft_atoi_ph(argv[1])))
		return (-1);
	if (init_data(data, argc, argv) == -1)
		return (-1);
	if (init_philo(data) == -1)
		return (-1);
	if (init_mutex(data) == -1)
		return (-1);
	if (init_forks(data) == -1)
		return (-1);
	data->t_start = get_time();
	return (0);
}
