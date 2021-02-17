#ifndef LOG_H
#define LOG_H

#include <ctime>

#include "event.h"
#include "event_log.h"
#include "utils.h"

namespace event_log
{
    namespace
    {
        constexpr char filename[] = "system.log";

        std::ofstream out(filename);

        void Flush() { out.flush(); }
    }  // namespace

    void LogEvent(const Event& e)
    {
        Flush();  // flush buffer
        out << e << " CPU_Queue_Size: " << std::left << std::setw(5) << cpu_queue.size()
            << "Network_Queue_Size: " << std::left << std::setw(5) << network_queue.size()
            << "Disk1_Queue_Size: " << std::left << std::setw(5) << disk1_queue.size()
            << "Disk2_Queue_Size: " << std::left << std::setw(5) << disk2_queue.size() << "\n";
    };

    void Close() { out.close(); }
}  // namespace event_log

#endif