/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:27:17 by marvin            #+#    #+#             */
/*   Updated: 2023/08/28 21:27:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2
# define DEAD 3
# define PICKING 4
# define FULL 5

# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				pid;
	int				eat_count;
	int				check;
	uint64_t		ttd;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	// int				*can_r;
	// int				*can_l;
	// int				have_r;
	// int				have_l;
	pthread_mutex_t	edit;
}	t_philo;

typedef struct s_data
{
	pthread_t		*thread;
	int				philo_num;
	int				someone_dead;
	int				eat_goal;
	int				im_full;
	int				finished;

	t_philo			*philos;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	uint64_t		t_die;
	uint64_t		t_start;

	pthread_mutex_t	*forks;
	//int				*can;
	pthread_mutex_t	edit;
	pthread_mutex_t	print;
}	t_data;

// check_input.c
int			is_digit(char c);
int			is_sign(char c);
int			is_valid_form(char *value);
int			ft_atoi_check(const char *str);
int			check_input(char **argv);

// initialize.c
int			init_data(t_data *data, int argc, char **argv);
int			init_philo(t_data *data);
int			init_fork(t_data *data);
int			init_can(t_data *data);
int			initialize(t_data *data, int argc, char **argv);

// create_thread.c
int			check_fin(t_data *data);
void		*philo(void *data);
int			join_thread(t_data *data);
int			create_thread(t_data *data);

// waiter.c
int			check_full(t_data *data);
void		*waitering(void *data);

// monitor.c
void		check_philo_stat(t_philo *philo);
void		*monitoring(void *dat);

// action.c
void		pickup_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eating(t_philo *philo);

// util.c
uint64_t	get_time(void);
void		print_msg(int state, t_philo *philo);
int			usleep_ph(useconds_t time);
int			ft_atoi_ph(const char *str);

// exit_philo.c
void		free_thread(t_data *data);
void		free_data(t_data *data);
int			exit_philo(t_data *data);

// main.c
int			error_philo(char *str);

#endif