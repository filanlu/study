#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <iostream>

using FUN = std::function<void(int)>;//定义别名
struct Task{
    FUN f;
    int args;
    Task(FUN fun =nullptr,int fd = -1):f(fun), args(fd){};
};
class ThreadPool
{
private:
    
    int _thread_count;
   std:: atomic_bool _is_running;
   std:: mutex _mtx;
   std:: condition_variable _con;
   std:: vector<std::thread> _thread_pool;
   std:: queue<Task> _task_queue;

private:
    void work();
    
public:
    ThreadPool(int thread_count);
    void start();
    void stop();
    void push_task(const Task &task);
    ~ThreadPool();
};

