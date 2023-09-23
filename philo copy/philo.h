/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:45:44 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/31 17:45:44 by hojakim          ###   ########.fr       */
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

// action.c
void		pick_right_left(t_philo *philo);
void		pick_left_right(t_philo *philo);
void		pickup_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eating(t_philo *philo);

// check_input.c
int			is_digit(char c);
int			is_sign(char c);
int			is_valid_form(char *value);
int			ft_atoi_check(const char *str);
int			check_input(int argc, char **argv);

// create_thread.c
int			check_fin(t_data *data);
int			join_thread(t_data *data);
int			create_thread(t_data *data);

// exit_philo.c
void		free_thread(t_data *data);
void		free_data(t_data *data);
int			exit_philo(t_data *data);

// initialize.c
int			init_data(t_data *data, int argc, char **argv);
int			init_philo(t_data *data);
int			init_fork(t_data *data);
int			initialize(t_data *data, int argc, char **argv);

// main.c
int			error_philo(char *str);

// th_monitor.c
void		check_philo_stat(t_philo *philo);
void		*monitoring(void *dat);

// th_philo.c
void		wait_for_start(t_philo *philo);
void		thinking(t_philo *philo);
void		lonely_philo(t_philo *philo);
void		*philo(void *phil);

// th_waiter.c
int			check_full(t_data *data);
void		*waitering(void *dat);

// util.c
uint64_t	get_time(void);
void		print_msg(int state, t_philo *philo);
int			sleep_ph(useconds_t time);
int			ft_atoi_ph(const char *str);

#endif