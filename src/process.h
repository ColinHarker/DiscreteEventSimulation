#ifndef PROCESS_H
#define PROCESS_H

static unsigned int MASTER_PID = 0;  // To keep track of all processes

class Process
{
 private:
    unsigned int PID;

 public:
    /** Creates unique PID for object
     */
    Process()
    {
        PID = MASTER_PID++;  // we set PID to current MASTER_PID
                             // then increment by one for the next process
    }
    Process(unsigned int _pid)
    {
        PID = _pid;
    }
    unsigned int GetPID() const
    {
        return PID;
    }
};

#endif