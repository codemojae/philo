/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:45:15 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/31 17:45:15 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (initialize(&data, argc, argv) == -1)
		return (exit_philo(&data));
	if (create_thread(&data) == -1)
		return (exit_philo(&data));
	exit_philo(&data);
	return (0);
}
