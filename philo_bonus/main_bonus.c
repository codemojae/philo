/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:49:46 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/25 18:37:43 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	t_data	data;
	int		err_code;

	if (argc < 5 || argc > 6)
	{
		printf("5 or 6 arguments.\n");
		return (1);
	}
	err_code = check_input(argc, argv);
	if (err_code == -1)
		return (1);
	if (initialize(&data, argc, argv) == 1)
		return (exit_philo(&data));
	// 아래서 프로세스 만들고, philo안의 thread까지 만들어야함.
	if (create_process(&data) == 1)
		return (exit_philo(&data));
	return (0);
}
