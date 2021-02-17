#include "config.h"

Configuration::Configuration()
{
    data.insert(std::make_pair("INIT_TIME", 0));
    data.insert(std::make_pair("FIN_TIME", 0));
    data.insert(std::make_pair("ARRIVE_MIN", 0));
    data.insert(std::make_pair("ARRIVE_MAX", 0));
    data.insert(std::make_pair("QUIT_PROB", 0));
    data.insert(std::make_pair("NETWORK_PROB", 0));
    data.insert(std::make_pair("CPU_MIN", 0));
    data.insert(std::make_pair("CPU_MAX", 0));
    data.insert(std::make_pair("DISK1_MIN", 0));
    data.insert(std::make_pair("DISK1_MAX", 0));
    data.insert(std::make_pair("DISK2_MIN", 0));
    data.insert(std::make_pair("DISK2_MAX", 0));
    data.insert(std::make_pair("NETWORK_MIN", 0));
    data.insert(std::make_pair("NETWORK_MAX", 0));
}

unsigned int Configuration::get_INIT_TIME() const { return data.find("INIT_TIME")->second; }
unsigned int Configuration::get_FIN_TIME() const { return data.find("FIN_TIME")->second; }
unsigned int Configuration::get_ARRIVE_MIN() const { return data.find("ARRIVE_MIN")->second; }
unsigned int Configuration::get_ARRIVE_MAX() const { return data.find("ARRIVE_MAX")->second; }
unsigned int Configuration::get_QUIT_PROB() const { return data.find("QUIT_PROB")->second; }
unsigned int Configuration::get_NETWORK_PROB() const { return data.find("NETWORK_PROB")->second; }
unsigned int Configuration::get_CPU_MIN() const { return data.find("CPU_MIN")->second; }
unsigned int Configuration::get_CPU_MAX() const { return data.find("CPU_MAX")->second; }
unsigned int Configuration::get_DISK1_MIN() const { return data.find("DISK1_MIN")->second; }
unsigned int Configuration::get_DISK1_MAX() const { return data.find("DISK1_MAX")->second; }
unsigned int Configuration::get_DISK2_MIN() const { return data.find("DISK2_MIN")->second; }
unsigned int Configuration::get_DISK2_MAX() const { return data.find("DISK2_MAX")->second; }
unsigned int Configuration::get_NETWORK_MIN() const { return data.find("NETWORK_MIN")->second; }
unsigned int Configuration::get_NETWORK_MAX() const { return data.find("NETWORK_MAX")->second; }