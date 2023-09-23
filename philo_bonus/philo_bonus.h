/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:43 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/23 08:48:33 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				pid;
	int				eat_count;
	int				check;
	uint64_t		ttd;
	pthread_mutex_t	*r_fork;
	int				get_r;
	pthread_mutex_t	*l_fork;
	int				get_l;
	pthread_mutex_t	edit;
}	t_philo;

// dead확인하려면 필요한것 ttd, t_die(고정))
// full을 확인하려면 필요한것 eat_count, check, im_full, eat_goal
// eating에 필요한것 t_die(고정), ttd, eat_count, 
typedef struct s_data
{
	pthread_t		*thread;
	int				philo_num;
	int				eat_goal;

	t_philo			*philos;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	uint64_t		t_die;
	uint64_t		t_start;

	int				ending;
	int				im_full;

	pthread_mutex_t	*forks;
	pthread_mutex_t	edit;
	pthread_mutex_t	print;
	pthread_mutex_t	start;
}	t_data;

#endif