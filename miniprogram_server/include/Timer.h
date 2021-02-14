#ifndef TIMER_H
#define TIMER_H
#include<iostream>
#include <queue>
#include <atomic>
#include <mutex>
#include <ctime>
#include <signal.h>
#include <sys/time.h>
#include <functional>

using namespace std;
using std::atomic_bool;
using std::lock_guard;
using std::mutex;
using std::priority_queue;
using std::time_t;
/** 
 *  
 * @param id              唯一的计时器 id. 
 * @param alarmTime      目的时间 
 ×
 */
class HttpServer;
//typedef void (HttpServer::*FUNC)(int); 
using TIMERCALLBACK = std::function<void(int)>; //定义函数指针

struct Timer
{
    int _id;
    time_t _alarmTime;
    Timer(int id, time_t interval);
    friend bool operator>(const Timer &t1, const Timer &t2);
};

//最小堆的自定义comp
inline bool operator>(const Timer &t1, const Timer &t2)
{
    return t1._alarmTime > t2._alarmTime;
};

class TimerManager
{
private:
    priority_queue<Timer, vector<Timer>, greater<Timer>> m_timerQueue; //堆管理计时器
    atomic_bool m_isTiktok;
    mutex m_mtx;
    TIMERCALLBACK m_slot; //信号处理函数

public:
    TimerManager(TIMERCALLBACK slot = nullptr);
    void run();

    void push(const Timer &tm);
    void pop();
    void stop();

    ~TimerManager();
};
#endif