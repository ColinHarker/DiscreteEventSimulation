#ifndef STATS_H
#define STATS_H

#include <tuple>

namespace stats
{
    extern unsigned int cpu_queue_usage;
    extern unsigned int disk1_queue_usage;
    extern unsigned int disk2_queue_usage;
    extern unsigned int network_queue_usage;

    extern unsigned int cpu_usage;
    extern unsigned int disk1_usage;
    extern unsigned int disk2_usage;
    extern unsigned int network_usage;

    extern unsigned int cpu_queue_sum_size;
    extern unsigned int disk1_queue_sum_size;
    extern unsigned int disk2_queue_sum_size;
    extern unsigned int network_queue_sum_size;

    extern unsigned int cpu_queue_max_size;
    extern unsigned int disk1_queue_max_size;
    extern unsigned int disk2_queue_max_size;
    extern unsigned int network_queue_max_size;

    extern double cpu_total_utilization_time;
    extern double disk1_total_utilization_time;
    extern double disk2_total_utilization_time;
    extern double network_total_utilization_time;

    extern double cpu_sum_response_time;
    extern double disk1_sum_response_time;
    extern double disk2_sum_response_time;
    extern double network_sum_response_time;

    extern unsigned int cpu_max_response_time;
    extern unsigned int disk1_max_response_time;
    extern unsigned int disk2_max_response_time;
    extern unsigned int network_max_response_time;

    extern double cpu_average_queue_size;
    extern double disk1_average_queue_size;
    extern double disk2_average_queue_size;
    extern double network_average_queue_size;

    extern double cpu_percent_utilization;
    extern double disk1_percent_utilization;
    extern double disk2_percent_utilization;
    extern double network_percent_utilization;

    extern unsigned int total_number_jobs;

    void Calculate();
    void Log();

}  // namespace stats
#endif