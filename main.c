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

void	check_leak(void)
{
	system("leaks philo");
}

void	test(t_philo *philo)
{
	*philo->can_l = 2;
	printf("%d\n", *philo->can_l);
	if (*philo->can_l == 2)
	{
		printf("wow\n");
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		err_code;

	atexit(check_leak);
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
	create_thread(&data);
	//usleep_ph(100);
	exit_philo(&data);
	return (0);
}

// 죽었을때 왜 안멈추니.
// 짝수의 경우 딜레이를 주지 않으면 모두가 잠드는 이상현상이 발생한다.
// 홀수의 경우 신경써주지 않으면 한명이 계속 먹지 못하고 죽게된다.
// detach 와 Join 의 사용법에 있어서 무언가 잘못되었나?

// --- 완료 --- 
// 4 410 200 200 일때 죽으면 안되는데, 1만 먹고 3이 못먹어서 죽는다.
// ㄴ 홀수번은 오른쪽부터, 짝수번은 왼쪽부터 잡는 방식으로 해결할 수 있을듯.
// 왜 식사횟수 1이면 안죽어?