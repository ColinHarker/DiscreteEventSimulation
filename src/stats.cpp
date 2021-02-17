#include <fstream>
#include <iostream>

#include "stats.h"
#include "utils.h"

namespace stats
{
    constexpr char filename[] = "stats.log";

    unsigned int cpu_queue_usage     = 0;
    unsigned int disk1_queue_usage   = 0;
    unsigned int disk2_queue_usage   = 0;
    unsigned int network_queue_usage = 0;

    unsigned int cpu_usage     = 0;
    unsigned int disk1_usage   = 0;
    unsigned int disk2_usage   = 0;
    unsigned int network_usage = 0;

    unsigned int cpu_queue_sum_size     = 0;
    unsigned int disk1_queue_sum_size   = 0;
    unsigned int disk2_queue_sum_size   = 0;
    unsigned int network_queue_sum_size = 0;

    unsigned int cpu_queue_max_size     = 0;
    unsigned int disk1_queue_max_size   = 0;
    unsigned int disk2_queue_max_size   = 0;
    unsigned int network_queue_max_size = 0;

    double cpu_total_utilization_time     = 0.f;
    double disk1_total_utilization_time   = 0.f;
    double disk2_total_utilization_time   = 0.f;
    double network_total_utilization_time = 0.f;

    double cpu_sum_response_time     = 0;
    double disk1_sum_response_time   = 0;
    double disk2_sum_response_time   = 0;
    double network_sum_response_time = 0;

    double cpu_average_response_time     = 0.f;
    double disk1_average_response_time   = 0.f;
    double disk2_average_response_time   = 0.f;
    double network_average_response_time = 0.f;

    unsigned int cpu_max_response_time     = 0;
    unsigned int disk1_max_response_time   = 0;
    unsigned int disk2_max_response_time   = 0;
    unsigned int network_max_response_time = 0;

    double cpu_average_queue_size     = 0;
    double disk1_average_queue_size   = 0;
    double disk2_average_queue_size   = 0;
    double network_average_queue_size = 0;

    double cpu_percent_utilization     = 0;
    double disk1_percent_utilization   = 0;
    double disk2_percent_utilization   = 0;
    double network_percent_utilization = 0;

    unsigned int total_number_jobs = 0;

    double throughput = 0.f;
}  // namespace stats

void stats::Calculate()
{
    cpu_average_queue_size     = static_cast<double>(cpu_queue_sum_size) / static_cast<double>(cpu_queue_usage);
    disk1_average_queue_size   = static_cast<double>(disk1_queue_sum_size) / static_cast<double>(disk1_queue_usage);
    disk2_average_queue_size   = static_cast<double>(disk2_queue_sum_size) / static_cast<double>(disk2_queue_usage);
    network_average_queue_size = static_cast<double>(network_queue_sum_size) / static_cast<double>(network_queue_usage);

    double total_system_time = static_cast<double>(global_config.get_FIN_TIME());

    cpu_percent_utilization     = (cpu_total_utilization_time / total_system_time) * 100;
    disk1_percent_utilization   = (disk1_total_utilization_time / total_system_time) * 100;
    disk2_percent_utilization   = (disk2_total_utilization_time / total_system_time) * 100;
    network_percent_utilization = (network_total_utilization_time / total_system_time) * 100;

    cpu_average_response_time     = cpu_sum_response_time / static_cast<double>(cpu_usage);
    disk1_average_response_time   = disk1_sum_response_time / static_cast<double>(disk1_usage);
    disk2_average_response_time   = disk2_sum_response_time / static_cast<double>(disk2_usage);
    network_average_response_time = network_sum_response_time / static_cast<double>(network_usage);

    throughput = total_system_time / static_cast<double>(total_number_jobs);
}

void stats::Log()
{
    std::ofstream out(filename);

    // CPU
    out << "CPU QUEUE:\n"
        << "\tAverage Size: " << cpu_average_queue_size << "\n\tMax Size: " << cpu_queue_max_size
        << "\n\tAverage Response Time: " << cpu_average_response_time << "\n\tMax Response Time: " << cpu_max_response_time << "\n\n";

    // DISK1
    out << "DISK1 QUEUE:\n"
        << "\tAverage Size: " << disk1_average_queue_size << "\n\tMax Size: " << disk1_queue_max_size
        << "\n\tAverage Response Time: " << disk1_average_response_time << "\n\tMax Response Time: " << disk1_max_response_time << "\n\n";

    // DISK2
    out << "DISK2 QUEUE:\n"
        << "\tAverage Size: " << disk2_average_queue_size << "\n\tMax Size: " << disk2_queue_max_size
        << "\n\tAverage Response Time: " << disk2_average_response_time << "\n\tMax Response Time: " << disk2_max_response_time << "\n\n";

    // NETWORK
    out << "NETWORK QUEUE:\n"
        << "\tAverage Size: " << network_average_queue_size << "\n\tMax Size: " << network_queue_max_size
        << "\n\tAverage Response Time: " << network_average_response_time << "\n\tMax Response Time: " << network_max_response_time
        << "\n\n";

    out << "SYSTEM THROUGHPUT: " << throughput << " time per job";

    out.close();
}