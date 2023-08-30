/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:55:08 by hojakim           #+#    #+#             */
/*   Updated: 2023/08/30 18:01:48 by hojakim          ###   ########.fr       */
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

int	ft_atoi_check(const char *str)
{
	long long	result;
	int			pm;

	result = 0;
	pm = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			pm = pm * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result < -2147483648 || result > 2147483647)
			return (-1);
		str++;
	}
	if (result * pm < 0)
		return (-1);
	return (0);
}


// 입력값 확인, 숫자인지, 양수인지 등.
int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_form(argv[i]))
			return (error_philo("invalid form"));
		if (ft_atoi_check(argv[i]) == -1)
			return (error_philo("Only Positive number in INT range"));
		i++;
	}
	return (0);
}
