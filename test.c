/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:34:31 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/23 11:09:48 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

void	test(int *n)
{
	n++;
}

int main(int argc, char const *argv[])
{
	int 	i = 0;
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * 5);
	while (i < 5)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			test(&n);
			printf("I'm %d child %d\n", i, n);
			return (0);
		}
		i++;
	}
	printf("I'm parent %d\n", n);
	return 0;
}
