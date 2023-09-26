/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:44:50 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/26 13:53:30 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (result * pm <= 0)
		return (-1);
	return (0);
}

int	check_input(int argc, char **argv)
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
	if (argc == 6 && ft_atoi_ph(argv[5]) == 0)
		return (error_philo("Philosophers need meal at least 1"));
	return (0);
}
