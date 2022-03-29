#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
//pthread_t *thread는 thread 식별자로서 성공적으로 생성됬는지 안됬는지 알수있게 햬준다.
//const pthread_attr_t *attr은 쓰레드의 특성을 지정할수 있고 기본적으로는 NULL을 사용한다.
//void *(*start_routine)(void *)은 분기시켜서 실행하는 thread 함수이다.
//void *arg는 thread함수 인자

// 쓰레드 함수
void *t_function(void *data) //3번째 인자로 분기시켜서 실행하는 thread 함수이다.
{
    int id;
    int i = 0;
    id = *((int *)data);

    while(1)
    {
        printf("%d : %d\n", id, i);
        i++;
        sleep(1);
    }
}

int main()
{
    pthread_t p_thread[2];
    int thr_id;
    int status;
    int a = 1;
    int b = 2;

    // 쓰레드 생성 아규먼트로 1 을 넘긴다.  
    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }

    // 쓰레드 생성 아규먼트로 2 를 넘긴다. 
    thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }

    // 쓰레드 종료를 기다린다. 
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
    //pthread_join은 thread가 종료될때 까지 기달려주며 thread자원을 해제시켜준다.
    
    return 0;
}
