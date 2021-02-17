#ifndef HANDLER_H
#define HANDLER_H

#include "event.h"
#include "event_log.h"
#include "utils.h"

namespace handler
{
    void ArriveSystem(const Event& current);
    void ExitSystem();
    void ArriveCpu(const Event& current);
    void ExitCpu(const Event& current);
    void ArriveDisk1(const Event& current);
    void ExitDisk1(const Event& current);
    void ArriveDisk2(const Event& current);
    void ExitDisk2(const Event& current);
    void ArriveNetwork(const Event& current);
    void ExitNetwork(const Event& current);
    void ExitSimulation();
}  // namespace handler
#endif