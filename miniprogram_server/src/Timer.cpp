#include "../include/Timer.h"
//Timer
Timer::Timer(int id, time_t interval) : _id(id)
{
    _alarmTime = std::time(nullptr) + interval;
}

//TimerManager
 TimerManager::TimerManager(pfunc slot = nullptr):_slot(slot), _is_tiktok(true)
 {
     
 }
/*new_value的it_interval 为周期触发的时间间隔
*new_value的it_value 优先指定了下次触发的时间间隔。
*即先倒计时it_value完触发 SIGALRM 变成周期性计时器
×每隔 it_interval 就触发SIGLRM
*/
void TimerManager::run(){
    
    itimerval new_value;
    new_value.it_interval.tv_sec =1;
    new_value.it_interval.tv_usec = 0;
    new_value.it_value .tv_sec = 1;
    new_value.it_value.tv_usec = 0;
    
    setitimer(ITIMER_REAL, &new_value,nullptr);

    signal(SIGALRM, _slot);
    while(_is_tiktok){
        ;
    }
}


TimerManager::~TimerManager(){
    if(_is_tiktok){
        stop();
    }
}

//TODO 在httpServer中声明个TimerManager，
//再定义个信号处理函数
//信号处理函数判断计时器的时间值（秒数）是否等于当前时间值
//如果等于： 调用TimerManager.pop();继续判断
//不等于结束