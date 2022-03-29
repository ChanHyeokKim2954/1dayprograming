#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//int pthread_detach(pthread_t th);
//main thread에서 pthread_create를 이용해 생성된 thread를 분리시킨다.
//설정해준 식별번호를 가진 thread를 detach 시키면 detach 되었을때와 thread가 종료되었을때
//join을 호출하지 않아도 즉시 모든 자원이 끊긴다.

// 쓰레드 함수
// 1초를 기다린후 아규먼트^2 을 리턴한다.
void *t_function(void *data)
{
    char a[100000];
    int num = *((int *)data);
 printf("Thread Start\n");
    sleep(5);
 printf("Thread end\n");
}

int main()
{
    pthread_t p_thread;
    int thr_id;
    int status;
    int a = 100;

 printf("Before Thread\n"); 
    thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    // 식별번호 p_thread 를 가지는 쓰레드를 detach 
    // 시켜준다. 
    pthread_detach(p_thread);
    pause();
    return 0;
}
//detach 시켰을때와 그렇지 않았을때의 메모리 상황이 다르다.
//detach를 사용하지 않았을 경우 함수가 종료되더라도 자원이 해제되지 않는다.
