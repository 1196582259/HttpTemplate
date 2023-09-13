#include <iostream>
#include <list>
#include <cstdio>
#include <pthread.h>
using namespace std;
#pragma commet(lib, "libpthread.dll.a")

#define NUM_THREADS 5

void *say_hello(void *args)
{
    cout << "Hello World!" << std::endl;
    return 0;
}

void p_thread_test()
{
    printf("hhhhhhhhh");
    pthread_t tids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if (ret != 0)
        {
            cout << "pthread_create error: error_code = " << ret << endl;
        }
    }
    pthread_exit(NULL);
}


/**
 * @class PThreadPool
 * @details 单例模式
*/
class PThreadPool
{
private:
    static PThreadPool *_instance;
    int _threadNum;
    int _maxThreadNum;
    pthread_t *tids;

    PThreadPool();

public:
    static PThreadPool *get_instance()
    {
        if (_instance == nullptr)
        {
            _instance = new PThreadPool();
        }
        return _instance;
    };

    ~PThreadPool();
    bool create_thread();
};
PThreadPool::PThreadPool(){
    _threadNum = 0;
    _maxThreadNum = 10; 
};
PThreadPool::~PThreadPool(){

};
PThreadPool PThreadPool::*_instance = nullptr;