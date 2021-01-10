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

typedef void (*pfunc)(int); //定义函数指针

class Timer
{
private:
    int _id;
    time_t _alarmTime;

public:
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
    priority_queue<Timer, vector<Timer>, greater<Timer>> timerQueue; //有够麻烦的
    atomic_bool _is_tiktok;
    mutex _mtx;
    pfunc _slot; //信号处理函数

public:
    TimerManager(pfunc slot = nullptr);
    void run();

    inline void push(Timer tm)
    {
        lock_guard<mutex> lg(_mtx);

        timerQueue.push(tm);
    }
    inline void TimerManager::pop()
    {
        lock_guard<mutex> lg(_mtx);
        timerQueue.pop();
    }
    inline void stop()
    {
        _is_tiktok = false;
    }

    ~TimerManager();

private:
    void pop();
};