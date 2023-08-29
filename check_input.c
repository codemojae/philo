/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:55:08 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/29 23:55:42 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	is_valid_form(char *value)
{
	int	i;

	i = 0;
	if (is_sign(value[i]) && value[i + 1] != '\0')
		i++;
	while (is_digit(value[i]) && value[i])
		i++;
	if (!is_digit(value[i]) && value[i] != '\0')
		return (0);
	return (1);
}

// 입력값 확인, 숫자인지, 양수인지 등.
int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_form(argv[i]))
			return (-1);
		i++;
	}
	return (0);
}