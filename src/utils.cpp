#include "utils.h"
#include "contants.h"

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

Configuration global_config;
unsigned int  system_time;

std::priority_queue<Event, std::vector<Event>, proj1::comparator> system_queue;

proj1::device_queue<Event> cpu_queue;
proj1::device_queue<Event> network_queue;
proj1::device_queue<Event> disk1_queue;
proj1::device_queue<Event> disk2_queue;

static std::random_device dev;  // used as a seed for the Mersenne generator
                                // generated from system's entropy pool via system calls

bool Init()
{
    return ParseConfig();
}

bool ParseConfig()
{
    std::ifstream file(constant::kConfigFileName);

    if(!file.is_open())
    {
        std::string config_file = constant::kConfigFileName;  // unsure why we need to do this, but std::cerr wont accept a namespace
        std::cerr << "ERROR: Opening config file [" + config_file + "]\n";
        return EXIT_FAILURE;
    }

    std::string line;
    std::string key;
    std::string value;

    while(getline(file, line))
    {
        std::stringstream ssline(line);
        ssline >> key >> value;
        std::map<std::string, unsigned int>::iterator it = global_config.data.find(key);
        if(it != global_config.data.end())
            it->second = std::stoul(value);
    }

    return true;
}

unsigned int GetRandomInt(int min, int max)
{
    std::mt19937 rng(dev());  // A Mersenne Twister pseudo-random generator
                              // of 32-bit numbers with a state size of 19937 bits.

    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);  // distribution in range [min, max]

    return dist(rng);
}
