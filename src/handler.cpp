#include "handler.h"
#include "stats.h"

void handler::ArriveSystem(const Event& current)
{
    if(cpu_queue.GetState() == flag::state::IDLE)
    {
        system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU, current.GetTime()));
    }
    else
    {
        event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU_QUEUE, current.GetTime()));
        cpu_queue.push(current);

        stats::cpu_queue_usage++;
        stats::cpu_queue_sum_size += cpu_queue.size();
    }

    unsigned int new_time = system_time + GetRandomInt(global_config.get_ARRIVE_MIN(), global_config.get_ARRIVE_MAX());
    system_queue.push(Event(Process(), flag::status::ARRIVE_SYSTEM, new_time));
}
void handler::ExitSystem() {}
void handler::ArriveCpu(const Event& current)
{
    cpu_queue.SetState(flag::state::BUSY);

    unsigned int event_time = GetRandomInt(global_config.get_CPU_MIN(), global_config.get_CPU_MAX());

    unsigned int exit_time = system_time + event_time;

    stats::cpu_total_utilization_time += event_time;
    stats::cpu_sum_response_time += event_time;
    stats::cpu_usage++;

    if(stats::cpu_max_response_time < event_time) stats::cpu_max_response_time = event_time;

    system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_CPU, exit_time));
}
void handler::ExitCpu(const Event& current)
{
    cpu_queue.SetState(flag::state::IDLE);

    unsigned int calculate_probability = GetRandomInt(1, 100);
    // system exit probaility
    if(global_config.get_QUIT_PROB() > calculate_probability)
    {
        system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_SYSTEM, current.GetTime()));
        return;
    }

    calculate_probability = GetRandomInt(1, 100);
    // network probability
    if(global_config.get_NETWORK_PROB() > calculate_probability)
    {
        if(network_queue.GetState() == flag::state::IDLE)
        {
            system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_NETWORK, current.GetTime()));
        }
        else
        {
            event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_NETWORK_QUEUE, current.GetTime()));
            network_queue.push(current);

            stats::network_queue_usage++;
            stats::network_queue_sum_size += network_queue.size();
        }
        return;
    }  // go to disk becuase we did not go to network
    else
    {
        if(disk1_queue.GetState() == flag::state::BUSY)
        {
            // if the disk1 is busy and the size is less than disk2
            // we add process to that queue
            if(disk1_queue.size() < disk2_queue.size())
            {
                event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_DISK1_QUEUE, current.GetTime()));
                disk1_queue.push(current);

                stats::disk1_queue_usage++;
                stats::disk1_queue_sum_size += disk1_queue.size();
            }
            // if disk1 queue is busy, and is the same size as disk 2,
            // then both disk queues are busy and of the same size
            // so we add the event to disk1 queue
            else if(disk1_queue.size() == disk2_queue.size())
            {
                event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_DISK1_QUEUE, current.GetTime()));
                disk1_queue.push(current);

                stats::disk1_queue_usage++;
                stats::disk1_queue_sum_size += disk1_queue.size();
            }
        }
        else if(disk2_queue.GetState() == flag::state::BUSY)
        {
            if(disk2_queue.size() < disk1_queue.size())
            {
                event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_DISK2_QUEUE, current.GetTime()));
                disk2_queue.push(current);

                stats::disk2_queue_usage++;
                stats::disk2_queue_sum_size += disk2_queue.size();
            }
        }
        // both disk queues are not busy, which means they are both empty, so we can go directly to disk1
        else
        {
            system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_DISK1, current.GetTime()));
        }
    }

    // when we exit a process from CPU, and we have other processes queued for CPU
    if(!cpu_queue.empty())
    {
        Event from_cpu_queue = cpu_queue.front();
        cpu_queue.pop();
        system_queue.push(Event(Process(from_cpu_queue.GetProcess().GetPID()), flag::status::ARRIVE_CPU, system_time));
    }
}
void handler::ArriveDisk1(const Event& current)
{
    disk1_queue.SetState(flag::state::BUSY);

    unsigned int event_time = GetRandomInt(global_config.get_DISK1_MIN(), global_config.get_DISK1_MAX());

    unsigned int exit_time = current.GetTime() + event_time;

    stats::disk1_total_utilization_time += event_time;
    stats::disk1_sum_response_time += event_time;
    stats::disk1_usage++;

    if(stats::disk1_max_response_time < event_time) stats::disk1_max_response_time = event_time;

    system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_DISK1, exit_time));
}
void handler::ExitDisk1(const Event& current)
{
    disk1_queue.SetState(flag::state::IDLE);

    if(cpu_queue.GetState() == flag::state::IDLE)
    {
        system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU, current.GetTime()));
    }
    else
    {
        cpu_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU, current.GetTime()));

        stats::cpu_queue_usage++;
        stats::cpu_queue_sum_size += cpu_queue.size();
    }
    if(!disk1_queue.empty())
    {
        Event from_disk1_queue = disk1_queue.front();
        disk1_queue.pop();
        system_queue.push(Event(Process(from_disk1_queue.GetProcess().GetPID()), flag::status::ARRIVE_DISK1, system_time));
    }
    event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_DISK1, current.GetTime()));
}
void handler::ArriveDisk2(const Event& current)
{
    disk2_queue.SetState(flag::state::BUSY);

    unsigned int event_time = GetRandomInt(global_config.get_DISK2_MIN(), global_config.get_DISK2_MAX());

    unsigned int exit_time = current.GetTime() + event_time;

    stats::disk2_total_utilization_time += event_time;
    stats::disk2_sum_response_time += event_time;
    stats::disk2_usage++;
    if(stats::disk2_max_response_time < event_time) stats::disk2_max_response_time = event_time;

    system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_DISK2, exit_time));
}
void handler::ExitDisk2(const Event& current)
{
    disk2_queue.SetState(flag::state::IDLE);

    if(cpu_queue.GetState() == flag::state::IDLE)
    {
        system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU, current.GetTime()));
    }
    else
    {
        cpu_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU, current.GetTime()));

        stats::cpu_queue_usage++;
        stats::cpu_queue_sum_size += cpu_queue.size();
    }
    if(!disk2_queue.empty())
    {
        Event from_disk2_queue = disk2_queue.front();
        disk2_queue.pop();
        system_queue.push(Event(Process(from_disk2_queue.GetProcess().GetPID()), flag::status::ARRIVE_DISK2, system_time));
    }
    event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_DISK2, current.GetTime()));
}
void handler::ArriveNetwork(const Event& current)
{
    network_queue.SetState(flag::state::BUSY);

    unsigned int event_time = GetRandomInt(global_config.get_NETWORK_MIN(), global_config.get_NETWORK_MAX());

    unsigned int exit_time = current.GetTime() + event_time;

    stats::network_total_utilization_time += exit_time - current.GetTime();
    stats::network_sum_response_time += event_time;
    stats::network_usage++;
    if(stats::network_max_response_time < event_time) stats::network_max_response_time = event_time;

    system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_NETWORK, exit_time));
}
void handler::ExitNetwork(const Event& current)
{
    network_queue.SetState(flag::state::IDLE);

    if(cpu_queue.GetState() == flag::state::IDLE)
    {
        system_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU, current.GetTime()));
    }
    else
    {
        cpu_queue.push(Event(Process(current.GetProcess().GetPID()), flag::status::ARRIVE_CPU, current.GetTime()));
        stats::cpu_queue_usage++;
        stats::cpu_queue_sum_size += cpu_queue.size();
    }
    if(!network_queue.empty())
    {
        Event from_network_queue = network_queue.front();
        network_queue.pop();
        system_queue.push(Event(Process(from_network_queue.GetProcess().GetPID()), flag::status::ARRIVE_NETWORK, system_time));
    }
    event_log::LogEvent(Event(Process(current.GetProcess().GetPID()), flag::status::EXIT_NETWORK, current.GetTime()));
}
void handler::ExitSimulation()
{
    stats::Calculate();
    stats::Log();

    event_log::Close();
    exit(EXIT_SUCCESS);
}