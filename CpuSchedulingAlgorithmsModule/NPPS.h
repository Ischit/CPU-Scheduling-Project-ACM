#ifndef NON_PREEMPTIVE_PRIORITY_SCHEDULING_H
#define NON_PREEMPTIVE_PRIORITY_SCHEDULING_H

#include "Process.h"
#include "SortingFunction.h"
#include "PrintTable.h"
#include <iostream>
#include <iomanip>
#include <limits> 
using namespace std;

void npps_calculate(vector<Process>& processes) {
    int time = 0;
    size_t len = processes.size();

    processes[0].setReturnTime(processes[0].getBurst());
    processes[0].setTurnaroundTime(processes[0].getReturnTime() - processes[0].getArriveTime());
    processes[0].setResponseTime(0);
    processes[0].setCompleted(true);

    time = processes[0].getBurst();

    while (true) {
        int minPriority = numeric_limits<int>::max();
        bool check = false;
        size_t minIndex = 0;

        for (size_t i = 1; i < len; i++) {
            if (!processes[i].isCompleted() && processes[i].getArriveTime() <= time &&
                processes[i].getPriority() < minPriority) {
                minPriority = processes[i].getPriority();
                minIndex = i;
                check = true;
            }
        }

        if (!check) break;

        processes[minIndex].setResponseTime(time - processes[minIndex].getArriveTime());
        processes[minIndex].setReturnTime(time + processes[minIndex].getBurst());
        processes[minIndex].setTurnaroundTime(processes[minIndex].getReturnTime() - processes[minIndex].getArriveTime());
        processes[minIndex].setWaitingTime(time - processes[minIndex].getArriveTime());
        processes[minIndex].setCompleted(true);

        time += processes[minIndex].getBurst();
    }
}

void npps_print_gantt_chart(const vector<Process>& processes) {
    cout << "\t ";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst(); j++) cout << "--";
        cout << " ";
    }

    cout << "\n\t|";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst() - 1; j++) cout << " ";
        cout << process.getId();
        for (int j = 0; j < process.getBurst() - 1; j++) cout << " ";
        cout << "|";
    }

    cout << "\n\t ";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst(); j++) cout << "--";
        cout << " ";
    }

    cout << "\n\t0";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst(); j++) cout << "  ";

        if (process.getReturnTime() > 9) cout << "\b";
        cout << process.getReturnTime();
    }

    cout << "\n";
}

void NPPS(vector<Process> processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    process_init(processes);
    merge_sort_by_arrive_time(processes, 0, processes.size()-1);

    npps_calculate(processes);

    for (const auto& process : processes) {
        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
        total_response_time += process.getResponseTime();
    }

    quick_sort_by_return_time(processes);

    cout << "\tNon-preemptive Priority Scheduling Algorithm\n\n";

    npps_print_gantt_chart(processes);

    cout << "\n\tAverage Waiting Time     : " << fixed << setprecision(2) << (double)total_waiting_time / processes.size() << "\n";
    cout << "\tAverage Turnaround Time  : " << fixed << setprecision(2) << (double)total_turnaround_time / processes.size() << "\n";
    cout << "\tAverage Response Time    : " << fixed << setprecision(2) << (double)total_response_time / processes.size() << "\n\n";

    print_table(processes);
}

#endif
