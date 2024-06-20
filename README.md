# CPU Scheduling Project

## Project Description
This project implements various CPU scheduling algorithms in C++. It simulates the behavior of these algorithms to help understand how different scheduling strategies affect process execution. The algorithms included are:

- First-Come, First-Served (FCFS)
- Shortest Remaining Time (SRT)
- Shortest Job First (SJF)
- Preemptive Priority Scheduling (PPS)
- Non Preemptive Priority Scheduling (NPPS)
- Round Robin (RR)
- Highest Response Ratio Next (HRN)

## How to Run the Project

### Dependencies
- C++ Compiler (e.g., g++)
- Make (optional, for using the provided Makefile)

### Setup Instructions
1. **Clone the repository:**
    ```bash
    git clone https://github.com/Ischit/ACM-Summer-Project-CPU-Scheduling.git
    ```

2. **Compile the project:**
    You can compile manually using g++:
    ```bash
    g++ -o cpu_scheduling CpuSchedulingSimulatorMain.cpp
    ```

3. **Run the executable:**
    ```bash
    ./cpu_scheduling
    ```

## Internal Working of the Project

### Theory
CPU scheduling is a fundamental concept in operating systems. It determines the order in which processes are executed by the CPU. Different algorithms have different criteria for scheduling, affecting system performance and process efficiency.

1. **First-Come, First-Served (FCFS):**
    - Processes are scheduled in the order they arrive.
    - Simple and easy to implement, but can lead to the "convoy effect."

2. **Shortest Job Next (SJN):**
    - Also known as Shortest Job First (SJF).
    - Processes with the shortest burst time are scheduled next.
    - Can lead to optimal average waiting time, but suffers from the "starvation" problem.

3. **Priority Scheduling:**
    - Each process is assigned a priority.
    - It can be preemptive as well as non preemptive.
    - The process with the highest priority is scheduled next.
    - Can be preemptive or non-preemptive. Preemptive scheduling can prevent low-priority processes from being starved.

4. **Round Robin (RR):**
    - Each process is assigned a fixed time slice (quantum).
    - Processes are scheduled in a cyclic order.
    - Fair and responsive, but the choice of time quantum is crucial for performance.

### Implementation
- Each scheduling algorithm is implemented in a separate C++ file.
- The input can be given in the process.txt where a sample testcase has been priviously created.
- The `CpuSchedulingSimulatorMain.cpp` file contains the user interface to select and run different scheduling algorithms.
- The project simulates the scheduling process by taking input for process burst times, priorities, and arrival times, then displays the order of execution and waiting times for each process.

## Learning Takeaways
- Understanding the mechanics of different CPU scheduling algorithms.
- Gaining experience in implementing and simulating these algorithms in C++.
- Learning about the trade-offs and practical considerations in CPU scheduling.
- Enhancing problem-solving and programming skills.

## Resources/References
- [Operating System Concepts by Abraham Silberschatz, Peter B. Galvin, and Greg Gagne](https://www.wiley.com/en-us/Operating+System+Concepts%2C+10th+Edition-p-9781119320913)
- [Wikipedia: CPU Scheduling](https://en.wikipedia.org/wiki/Scheduling_(computing))
- [GeeksforGeeks: CPU Scheduling Algorithms](https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/)

Feel free to explore, modify, and improve the project. Contributions are welcome!

