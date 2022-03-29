#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

//void pthrad_cleanup_push(void (*routine) (void *), void *arg);
//위 함수를 사용하는 목적은 cleanup handlers를 인스톨하기 위해서 사용된다.
//pthread_exit(3)가 호출되어서 쓰레드가 종료될때 pthread_cleanup_push 에 의해서 인스톨된 함수가 호출된다
//routine은 쓰레드가 종료될때 호출되는 함수이다
//arg는 thread 함수 인자
//cleanup handlers 는 주로 자원을 되돌려주거나, mutex 잠금등의 해제를 위한 용도로 사용된다. 
//만약 mutex 영역에서 pthread_exit 가 호출되어 버릴경우 다른쓰레드에서 영원히 block 될수 있기 때문이다. 
//또한 malloc 으로 할당받은 메모리, 열린 파일지정자를 닫기 위해서도 사용한다

// 쓰레드 함수
// 1초를 기다린후 아규먼트^2 을 리턴한다.

char *mydata;
void cleanup(void *);
void *t_function(void *data)
{
    int num = *((int *)data);
    int i = 0;
    int a = 1;
    // cleanup handler 로 cleanup 함수를 
    // 지정한다. 
    pthread_cleanup_push(cleanup, (void *)&a);
    mydata = (char *)malloc(1000);
    while(1)
    {
        if (i == 3)
        {
            // pthread_exit 가 호출되면서 
            // cleanup 을 호출하게 된다. 
            pthread_exit(0);
            return 1;
        }
        printf("loop %d\n", i);
        i++;
        sleep(1);
    }
    pthread_cleanup_pop(0);
}


int main()
{
    pthread_t p_thread;
    int thr_id;
    int status;
    int a = 100;


    thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    pthread_join(p_thread, (void **)&status);
    printf("Join finish\n");
}

// cleanup handler
void cleanup(void *myarg)
{
    printf("thread is clean up\n");
    printf("resource free\n");
    free(mydata);
}
   
//void pthread_cleanup_pop(int execute);
//pthread_cleanup_push 와 함께 사용되며, install 된 cleanup handler 을 제거하기 위해서 사용된다.
//만약 execute 가 0 이라면, pthread_cleanup_push 에 의해 인스톨된 cleanup handler 를 (실행시키지 않고)삭제만 시킨다. 
//0 이 아닌 숫자라면 cleanup handler 을 실행시키고 삭제 된다.
