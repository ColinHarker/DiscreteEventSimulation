#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <random>

class Configuration
{
 public:
    Configuration();

    std::map<std::string, unsigned int> data;

    unsigned int get_INIT_TIME() const;
    unsigned int get_FIN_TIME() const;
    unsigned int get_ARRIVE_MIN() const;
    unsigned int get_ARRIVE_MAX() const;
    unsigned int get_QUIT_PROB() const;
    unsigned int get_NETWORK_PROB() const;
    unsigned int get_CPU_MIN() const;
    unsigned int get_CPU_MAX() const;
    unsigned int get_DISK1_MIN() const;
    unsigned int get_DISK1_MAX() const;
    unsigned int get_DISK2_MIN() const;
    unsigned int get_DISK2_MAX() const;
    unsigned int get_NETWORK_MIN() const;
    unsigned int get_NETWORK_MAX() const;
};

#endif