#ifndef UTILS_H
#define UTILS_H

#include <deque>
#include <queue>

#include "config.h"
#include "event.h"

extern Configuration global_config;
extern unsigned int  system_time;

unsigned int GetRandomInt(int min, int max);

bool Init();
bool ParseConfig();

namespace proj1
{
    template<typename T, typename Container = std::deque<T>>
    class device_queue : public std::queue<T, Container>
    {
     private:
        // device is idle when queue is instantiated
        flag::state state = flag::state::IDLE;

     public:
        void SetState(const flag::state& _state)
        {
            state = _state;
        }

        flag::state GetState() const
        {
            return state;
        }
    };

    struct comparator
    {
        bool operator()(Event& a, Event& b)
        {
            return a.GetTime() > b.GetTime();
        }
    };
}  // namespace proj1

extern std::priority_queue<Event, std::vector<Event>, proj1::comparator> system_queue;

extern proj1::device_queue<Event> cpu_queue;
extern proj1::device_queue<Event> network_queue;
extern proj1::device_queue<Event> disk1_queue;
extern proj1::device_queue<Event> disk2_queue;

#endif