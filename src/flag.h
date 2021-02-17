#ifndef FLAG_H
#define FLAG_H

namespace flag
{
    enum class state : int
    {
        IDLE,
        BUSY
    };

    enum class status : int
    {
        ARRIVE_SYSTEM,
        EXIT_SYSTEM,
        ARRIVE_CPU,
        EXIT_CPU,
        ARRIVE_DISK1,
        EXIT_DISK1,
        ARRIVE_DISK2,
        EXIT_DISK2,
        ARRIVE_NETWORK,
        EXIT_NETWORK,
        EXIT_SIMULATION,
        ARRIVE_DISK1_QUEUE,
        ARRIVE_DISK2_QUEUE,
        ARRIVE_NETWORK_QUEUE,
        ARRIVE_CPU_QUEUE
    };
}  // namespace flag

inline std::ostream& operator<<(std::ostream& os, const flag::status& s)
{
    using namespace flag;
    switch(s)
    {
        case status::ARRIVE_SYSTEM:
            os << "ARRIVE_SYSTEM";
            break;
        case status::EXIT_SYSTEM:
            os << "EXIT_SYSTEM";
            break;
        case status::ARRIVE_CPU:
            os << "ARRIVE_CPU";
            break;
        case status::EXIT_CPU:
            os << "EXIT_CPU";
            break;
        case status::ARRIVE_DISK1:
            os << "ARRIVE_DISK1";
            break;
        case status::EXIT_DISK1:
            os << "EXIT_DISK1";
            break;
        case status::ARRIVE_DISK2:
            os << "ARRIVE_DISK2";
            break;
        case status::EXIT_DISK2:
            os << "EXIT_DISK2";
            break;
        case status::ARRIVE_NETWORK:
            os << "ARRIVE_NETWORK";
            break;
        case status::EXIT_NETWORK:
            os << "EXIT_NETWORK";
            break;
        case status::EXIT_SIMULATION:
            os << "EXIT_SIMULATION";
            break;
        case status::ARRIVE_DISK1_QUEUE:
            os << "ARRIVE_DISK1_QUEUE";
            break;
        case status::ARRIVE_DISK2_QUEUE:
            os << "ARRIVE_DISK2_QUEUE";
            break;
        case status::ARRIVE_NETWORK_QUEUE:
            os << "ARRIVE_NETWORK_QUEUE";
            break;
        case status::ARRIVE_CPU_QUEUE:
            os << "ARRIVE_CPU_QUEUE";
            break;
    }
    return os;
}
#endif
