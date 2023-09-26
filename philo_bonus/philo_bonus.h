/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:09:43 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/26 15:15:01 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
//# include <fcntl.h>
//# include <sys/stat.h>

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
	int				id;
	int				eat_count;
	int				eating;
	int				full;
	uint64_t		ttd;
	pthread_t		thread;
}	t_philo;

// dead확인하려면 필요한것 ttd, t_die(고정))
// full을 확인하려면 필요한것 eat_count, check, im_full, eat_goal
// eating에 필요한것 t_die(고정), ttd, eat_count, 
typedef struct s_data
{
	int				philo_num;
	int				eat_goal;

	t_philo			*philos;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	uint64_t		t_die;
	uint64_t		t_start;

	int				ending;
	int				im_full;

	sem_t			*forks;
	sem_t			*print;
	sem_t			*dead;
}	t_data;

//action_bonus.c
void		pickup_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//check_input_bonus.c
int			check_input(int argc, char **argv);

//create_process_bonus.c
int			create_process(t_data *data);

//exit_philo_bonus.c
int			exit_philo(t_data *data);

//initialize_bonus.c
int			init_sem(t_data *data);
int			init_data(t_data *data, int argc, char **argv);
int			init_philo(t_data *data);
int			initialize(t_data *data, int argc, char **argv);

//main_bonus.c
int			error_philo(char *str);

//monitor_bonus.c
void		*monitoring(void *dat);

// util_bonus.c
uint64_t	get_time(void);
void		print_msg(int state, t_philo *philo);
int			sleep_ph(useconds_t time);
int			ft_atoi_ph(const char *str);

#endif