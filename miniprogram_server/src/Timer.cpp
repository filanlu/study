#include "../include/Timer.h"
//Timer
Timer::Timer(int id, time_t interval) : _id(id)
{
    _alarmTime = std::time(nullptr) + interval;
    // std::cout << "目标时间：" << _alarmTime << std::endl;
}

//TimerManager
TimerManager::TimerManager(TIMERCALLBACK slot) : m_slot(slot)
{
}
/*new_value的it_interval 为周期触发的时间间隔
*new_value的it_value 优先指定了下次触发的时间间隔。
*即先倒计时it_value完触发 SIGALRM 变成周期性计时器
×每隔 it_interval 就触发SIGLRM
*/
void TimerManager::push(const Timer &tm)
{
    lock_guard<mutex> lg(m_mtx);
    m_timerQueue.push(tm);
    // std::cout << "push后剩下的计数器数：" << m_timerQueue.size() << std::endl;
}

void TimerManager::pop()
{
    lock_guard<mutex> lg(m_mtx);
    m_timerQueue.pop();
}

void TimerManager::stop()
{
    m_isTiktok = false;
}
 void initTimeval(timeval &timeout)
{
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
}
void TimerManager::run()
{
    m_isTiktok = true;
    timeval timeout;
    initTimeval(timeout);

    while (m_isTiktok)
    {
        // std::cout << "select前" << time(nullptr) << std::endl;
        select(0, NULL, NULL, NULL, &timeout);
        initTimeval(timeout);
        // std::cout << "select后" << time(nullptr) << std::endl;

        while (!m_timerQueue.empty())
        {

            auto it = m_timerQueue.top();
            auto t = time(nullptr);
            // std::cout<< "当前时间："<<t<<std::endl;
            if (it._alarmTime <= t)
            {
                if (m_slot)
                    m_slot(it._id); //删除房间
                m_timerQueue.pop(); //删除定时器
                // std::cout << "释放后剩下的计数器数：" << m_timerQueue.size() << std::endl;
            }
            else
                break;
        }
    }
}

TimerManager::~TimerManager()
{
    if (m_isTiktok)
    {
        stop();
    }
}

//TODO 在httpServer中声明个TimerManager，
//再定义个信号处理函数
//信号处理函数判断计时器的时间值（秒数）是否等于当前时间值
//如果等于： 调用TimerManager.pop();继续判断
//不等于结束
//修改方案：
//采用select则不需要使用软中断的方式去处理计时器。
//则可以把时间处理挪到用户态
//todo::队列的同步互斥。