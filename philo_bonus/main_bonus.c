/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:49:46 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/30 01:59:07 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <semaphore.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

int	error_philo(char *str)
{
	printf("%s\n", str);
	return (-1);
}

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
	memset(&data, 0, sizeof(t_data));
	if (initialize(&data, argc, argv) == 1)
		return (exit_philo(&data));
	if (create_process(&data) == 1)
		return (exit_philo(&data));
	exit_philo(&data);
	return (0);
}
