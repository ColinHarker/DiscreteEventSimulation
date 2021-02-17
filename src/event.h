#ifndef EVENT_H
#define EVENT_H

#include <iomanip>
#include <iostream>

#include "flag.h"
#include "process.h"

class Event
{
 private:
    Process      process;
    flag::status event_status;
    unsigned int time;

 public:
    /**
     * @param _process process that this event is attributed with, Takes Process object
     * @param _status status of the event, takes enum class [flag::status]
     * @param _time time that this event will be executed
     */
    Event(Process _process, flag::status _status, unsigned int _time) : process(_process), event_status(_status), time(_time) {}

    flag::status GetStatus() const
    {
        return event_status;
    }

    Process GetProcess() const
    {
        return process;
    }

    unsigned int GetTime() const
    {
        return time;
    }

    friend std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        {
            os << "Time: " << std::left << std::setw(6) << e.GetTime() << " PID: " << std::left << std::setw(6) << e.GetProcess().GetPID()
               << " Event: " << std::left << std::setw(20) << e.GetStatus();
            return os;
        }
    }
};
#endif