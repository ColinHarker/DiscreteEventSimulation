#include <iostream>
#include <random>

#include "event_log.h"
#include "handler.h"
#include "stats.h"
#include "utils.h"

int main(int argc, char** argv)
{
    // initializes runtime variables
    // throws error for failure
    if(!Init())
    {
        return EXIT_FAILURE;
    }

    system_time = global_config.get_INIT_TIME();

    system_queue.push(Event(Process(), flag::status::EXIT_SIMULATION, global_config.get_FIN_TIME()));
    system_queue.push(Event(Process(), flag::status::ARRIVE_SYSTEM, system_time));

    while(system_queue.size() > 0)
    {
        const Event current = system_queue.top();
        system_time         = current.GetTime();
        system_queue.pop();

        event_log::LogEvent(current);

        using namespace flag;
        switch(current.GetStatus())
        {
            case status::ARRIVE_SYSTEM:
                handler::ArriveSystem(current);
                break;
            case status::EXIT_SYSTEM:
                handler::ExitSystem();
                break;
            case status::ARRIVE_CPU:
                handler::ArriveCpu(current);
                break;
            case status::EXIT_CPU:
                handler::ExitCpu(current);
                break;
            case status::ARRIVE_DISK1:
                handler::ArriveDisk1(current);
                break;
            case status::EXIT_DISK1:
                handler::ExitDisk1(current);
                break;
            case status::ARRIVE_DISK2:
                handler::ArriveDisk2(current);
                break;
            case status::EXIT_DISK2:
                handler::ExitDisk2(current);
                break;
            case status::ARRIVE_NETWORK:
                handler::ArriveNetwork(current);
                break;
            case status::EXIT_NETWORK:
                handler::ExitNetwork(current);
                break;
            case status::EXIT_SIMULATION:
                handler::ExitSimulation();
                break;
            default:
                std::cerr << "How did this happen"
                          << "\n";
                return EXIT_FAILURE;
        }

        if(stats::cpu_queue_max_size < cpu_queue.size()) stats::cpu_queue_max_size = cpu_queue.size();
        if(stats::disk1_queue_max_size < disk1_queue.size()) stats::disk1_queue_max_size = disk1_queue.size();
        if(stats::disk2_queue_max_size < disk2_queue.size()) stats::disk2_queue_max_size = disk2_queue.size();
        if(stats::network_queue_max_size < network_queue.size()) stats::network_queue_max_size = network_queue.size();

        stats::total_number_jobs++;
    }

    event_log::Close();

    return EXIT_SUCCESS;
}