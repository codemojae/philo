/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:26:03 by marvin            #+#    #+#             */
/*   Updated: 2023/08/28 21:26:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_philo(char *str)
{
	printf("%s\n", str);
	return (-1);
}

int	one_philo(t_data *data)
{
	printf("%llu 1 died\n", data->t_die);
	return (0);
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
	err_code = check_input(argv);
	if (err_code == -1) // 입력형태 오류.
		return (1);
	if (initialize(&data, argc, argv) == -1) // 오류시 free 필요.
		return (1);
	if (data.philo_num == 1)
		return (one_philo(&data));
	create_thread(&data);
	exit_philo(&data);
	return (0);
}

/* 최소 식사횟수를 충족하는지 확인하는건 tom

data쪽에 finished 를 넣어서 이것만 확인하는걸로.
eating 에서 철학자의 식사횟수를 담당하고, 식사 수가 목표치에 도달하면 finished++;*/