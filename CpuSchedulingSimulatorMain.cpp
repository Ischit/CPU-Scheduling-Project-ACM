#include "CpuSchedulingAlgorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int process_count = 0;
    int i = 0;

    Quantum quantum;
    vector<Process> processes;

    ifstream fp("process.txt");

    if (!fp) {
        cout << "FILE OPEN ERROR!" << endl;
        return 0;
    }

    fp >> process_count;

    processes.resize(process_count);

    while (i < process_count) {
        string id;
        int arrive_time, burst, priority;
        fp >> id >> arrive_time >> burst >> priority;
        processes[i].setId(id);
        processes[i].setArriveTime(arrive_time);
        processes[i].setBurst(burst);
        processes[i].setPriority(priority);
        i++;
    }

    fp >> quantum;

    cout << "┏                                                                                                                             ┓\n\n";
    RR(processes, quantum);
    cout << "┗                                                                                                                             ┛\n\n";

    cout << "┏                                                                                                                             ┓\n\n";
    FCFS(processes);
    cout << "┗                                                                                                                             ┛\n\n";

    cout << "┏                                                                                                                             ┓\n\n";
    SJF(processes);
    cout << "┗                                                                                                                             ┛\n\n";

    cout << "┏                                                                                                                             ┓\n\n";
    HRN(processes);
    cout << "┗                                                                                                                             ┛\n\n";

    cout << "┏                                                                                                                             ┓\n\n";
    NPPS(processes);
    cout << "┗                                                                                                                             ┛\n\n";

    cout << "┏                                                                                                                             ┓\n\n";
    PPS(processes);
    cout << "┗                                                                                                                             ┛\n\n";

    cout << "┏                                                                                                                             ┓\n\n";
    SRT(processes);
    cout << "┗                                                                                                                             ┛\n\n";

    fp.close();

    system("pause");

    return 0;
}