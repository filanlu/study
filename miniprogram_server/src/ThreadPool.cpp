#include "../include/ThreadPool.h"
ThreadPool::ThreadPool(int thread_count) : _thread_count(thread_count), _is_running(false)
{
   
}

void ThreadPool::start()
{
    _is_running = true;
    for (int i = 0; i < _thread_count; i++)
    {
        _thread_pool.emplace_back(std::thread(&ThreadPool::work, this));
    }
}

void ThreadPool::stop()
{
    _is_running = false;
    std::unique_lock<std::mutex> lx(_mtx);
    _con.notify_all();
    for (auto &t : _thread_pool)
    {
        if (t.joinable())
            t.join();
    }
}

void ThreadPool::push_task(const Task &task)
{
    if (!_is_running)
    {
        std::cout << "线程池已关闭" << std::endl;
        return;
    }
        
   
    std::unique_lock<std::mutex> lx(_mtx);
    _task_queue.push(task);
    _con.notify_one();
}
void ThreadPool::work()
{

    while (_is_running)
    {
        Task task ;
        {

             std::unique_lock<std::mutex> lx(_mtx);
            if (!_task_queue.empty()){
        
            task = _task_queue.front();
            _task_queue.pop(); 
            }
            else if(_is_running && _task_queue.empty()){
                _con.wait(lx);//con.wait(lx)会自动释放锁
            }
           
            // std::unique_lock<std::mutex> lx(_mtx);/*错误代码
            // if (_task_queue.empty())               con.wait释放锁后，取任务将不具有原子性
            //     _con.wait(lx);                     导致不同线程同时取同一元素导致段错误。
            // std::cout << "bk2" << std::endl;         
            // task = _task_queue.front();          */
            // _task_queue.pop(); 
        }
       
        if (task.f!=nullptr)
        {
           
            task.f(task.args);
        }
        

    }
    printf("end work thread: %d\n", std::this_thread::get_id());
}

ThreadPool::~ThreadPool()
{
    if (_is_running)
        stop();
}
