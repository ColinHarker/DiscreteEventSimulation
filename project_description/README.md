# Project 1
- The priority_queue is made up of events and is the driver of the simulation. Time moves forward only when an event is popped from the front of the queue. Depending on what the event is, dictates what actions will be taken during that cycle. Each event has a time it will be executed by the system (which is how we sort the prio_queue), and it has a process assosiated with is as well. 
- We have 4 devices the processes can go to, every process goes to the CPU, and then after, based on a set probability, it can either exit the system or procede to;
  - disk1
  - disk2
  - network
- An Event arriving at a device will be an `EVENT_ARRIVES` event, and will have a time assosiated when that event happens. We also generate a time for when the event will end, `EVENT_EXIT`. If the Device is `IDLE`, meaning that there is no event being worked on and nothing in the queue, then the event that arrived can begin getting worked on imediattly and the devices stated will be changed to `BUSY`. If the device is `BUSY`, the event is added to the FIFO queue for that devices and waits to be worked on.
- It is to be noted that with the `EVENT_ARRIVES` and `EVENT_EXIT` event, although they are stored as seperate event objects in the priority_queue, the process that is assosiated with them will be the same.
- For example:
  - | Time | Event         | PID |
    | ---- | ------------- | --- |
    | 0    | ARRIVE_SYSTEM | 1   |
    | 10   | ARRIVE_CPU    | 1   |
    | 15   | ARRIVE_SYSTEM | 2   |
    | 20   | EXIT_CPU      | 1   |
    | 25   | ARRIVE_CPU    | 2   |

- Queues
  - Event Queue (Priority Queue): Store all events that happen in the system, in the order they are to be executed
  - CPU Queue (FIFO Queue): While CPU is busy, process are held here
  - Disk1 Queue (FIFO Queue): While Disk1 is busy, process are held here
  - Disk2 Queue (FIFO Queue): While Disk2 is busy, process are held here
  - Network Queue (FIFO Queue): While Network is busy, events are stored here


- Time in this simulation advances based on the time the events take. In the priority queue if `SIMULATION_TIME = 0` and the first element of the queue happens when `job1_TIME = 15`, then when the element gets popped off the queue it sets the `SIMULATION_TIME = JOB1_TIME = 15 `

- The priority queue makes sure that the simulation is executing the events in the proper order. The events that are given priority are the ones with the lowest time. If we have 4 events `Event1_TIME = 20, EVENT2_TIME = 35, EVENT3_TIME = 14, EVENT4_TIME = 25`. Then the queue would order, and pop items off in this order. `EVENT3_TIME = 14 <- Event1_TIME = 20 <- EVENT4_TIME = 25 <- EVENT2_TIME = 35`

- Events will be entered into the prioriy queue when;
  - Job enters the system
  - Job exits the system
  - Job arrives at CPU
  - Job finishes at CPU
  - Job arrives at I/O device
  - Job finishes at I/O device

- Depending on what the event is, we have different parameters where we generate a time value for how long this event should take. Once this duration has been calculated we get the time value for the priority queue by, `EVENT_TIME = SIMULATION_TIME + EVENT_DURATION`

- an event is removed or 'popped' off the queue when it is the first in line, I.E it has the lowest time value, and therefore is the next event in line to be executed. 

- When we remove an event from the priority queue, we then figure out the arrival time of the next event. We calulate this arrival time by generating a random integer between `ARRIVE_MIN and ARRIVE_MAX`, that are found in the config file. Once this integer is calulated we find the arrival time by `ARRIVAL_TIME = SIMULATION_TIME + RANDOM_INT`