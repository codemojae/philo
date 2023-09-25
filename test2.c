#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void test(int n) {
    srand(time(NULL)); // 난수 생성을 위해 시드 초기화

    int sleep_time = (rand() % 5) + 1; // 1초에서 5초 사이의 랜덤한 시간
    printf("Child %d will sleep for %d seconds\n", n, sleep_time);
    sleep(5 - (n % 2)); // 랜덤한 시간 동안 쉼

    if (n == 3) {
        exit(1); // 자식 프로세스에서 exit(1)로 종료
    }
    exit(0); // 나머지 자식 프로세스에서 exit(0)로 종료
}

int main(int argc, char const *argv[]) {
    int i = 0;
    pid_t pid;
    int status;

    while (i < 5) {
        pid = fork();
        usleep(3333);
        if (pid == 0) {
            test(i);
            printf("I'm %d child\n", i);
            return 0;
        }
        i++;
    }

    // 모든 자식 프로세스의 종료를 기다립니다.
    for (i = 0; i < 5; i++) {
        pid_t child_pid = waitpid(-1, &status, 0);
        if ((status >> 8) == 0) {
            printf("Child %d (PID %d) exited with exit(0)\n", i, child_pid);
        } else if ((status >> 8) == 2) {
            printf("Child %d (PID %d) exited with exit(1)\n", i, child_pid);
            printf("EXIT!\n");
            return 0;
        } else {
            printf("Child %d (PID %d) exited with unknown exit code: %d\n", i, child_pid, (status >> 8));
        }
    }

    printf("I'm parent\n");
    return 0;
}
