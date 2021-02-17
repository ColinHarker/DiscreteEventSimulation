#include <fstream>
#include <string>

#include "event.h"

namespace event_log
{
    void LogEvent(const Event& e);
    void Close();
}  // namespace event_log