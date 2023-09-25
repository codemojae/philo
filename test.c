/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:34:31 by hojakim           #+#    #+#             */
/*   Updated: 2023/09/26 00:28:09 by hojakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

void *test_thread(void *arg) {
    int num = *(int *)arg; // 포인터로 전달된 데이터를 정수로 형변환하여 사용

    if (num == 3) {
        printf("Thread: 333333\n");
        exit(1); // 전체 스레드가 종료되는가?
    }
    return NULL;
}

void test(int n) {
    pthread_t thread;

    pthread_create(&thread, NULL, &test_thread, &n);
    usleep(1000);
    printf("%d here\n", n);
    exit(0); // 
}

int main(int argc, char const *argv[]) {
    int i = 0;
	int status = 0;
    pid_t *pid;

    pid = malloc(sizeof(pid_t) * 5);
    while (i < 5) {
        pid[i] = fork();
        if (pid[i] == 0) {
            test(i);
            return 0;
        }
        i++;
    }
	while (i < 5) {
		waitpid(-1, )
	}
    printf("I'm parent\n");
    return 0;
}

