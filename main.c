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
	if (err_code == -1)
		return (1);
	if (initialize(&data, argc, argv) == -1)
		return (exit_philo(&data));
	if (create_thread(&data) == -1)
		return (exit_philo(&data));
	exit_philo(&data);
	return (0);
}

// 수많은 데이터레이스를 확인했다. 그 기록
// ㄴ eating에 뮤텍스 삽입

// 범위를 초과한 입력대처. "   205010520" 같은 형태의 입력 대처.

// 짝수의 경우 딜레이를 주지 않으면 모두가 잠드는 이상현상이 발생한다.
// detach 와 Join 의 사용법에 있어서 무언가 잘못되었나?

// --- 완료 --- 
// 4 410 200 200 일때 죽으면 안되는데, 1만 먹고 3이 못먹어서 죽는다.
// ㄴ 홀수번은 오른쪽부터, 짝수번은 왼쪽부터 잡는 방식으로 해결할 수 있을듯.
// 왜 식사횟수 1이면 안죽어?
// 홀수의 경우 신경써주지 않으면 한명이 계속 먹지 못하고 죽게된다.

// 수가 많아지면 맛이 가네.
// ㄴ 스레드를 생성하는 도중에 짝수 philo를 먼저 실행하려고 준 간격인 1ms를 초과해버렸다.
// ㄴ 그래서 짝수먼저 모두 선점하고 시작하는 부분이 되지 않았다.
// ㄴ 수에 따라 좀 늘려야 할듯.

// 죽었을때 바로 멈추는 방법? detach를 사용하면 되는데 segfault를 못잡는다.
// ㄴ 출력을 막아버렸다....

// 해제해야하는것, data -> malloc thread, forks, can, philos 
// mutex forks, edit, print
// pthread_cancel을 사용할 수가 없어서 그냥 반환하기로.