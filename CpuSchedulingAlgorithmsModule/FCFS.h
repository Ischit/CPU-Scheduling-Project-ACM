#ifndef FIRST_COME_FIRST_SERVED_H
#define FIRST_COME_FIRST_SERVED_H

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void fcfs_print_gantt_chart(const vector<Process>& processes) {
    int j;

    cout << "\t ";
    for (const auto& process : processes) {
        for (j = 0; j < process.getBurst(); j++) cout << "--";
        cout << " ";
    }
    cout << "\n\t|";

    for (const auto& process : processes) {
        for (j = 0; j < process.getBurst() - 1; j++) cout << " ";
        cout << process.getId();
        for (j = 0; j < process.getBurst() - 1; j++) cout << " ";
        cout << "|";
    }

    cout << "\n\t ";

    for (const auto& process : processes) {
        for (j = 0; j < process.getBurst(); j++) cout << "--";
        cout << " ";
    }

    cout << "\n\t0";

    for (const auto& process : processes) {
        for (j = 0; j < process.getBurst(); j++) cout << "  ";
        cout << "\b" << process.getReturnTime();
    }

    cout << "\n";
}

void FCFS(vector<Process> processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;
    int total_return_time = 0;

    process_init(processes);

    merge_sort_by_arrive_time(processes, 0, processes.size() - 1);

    processes[0].setReturnTime(processes[0].getBurst());
    processes[0].setTurnaroundTime(processes[0].getReturnTime() - processes[0].getArriveTime());
    processes[0].setResponseTime(0);
    processes[0].setWaitingTime(0);

    total_response_time += processes[0].getResponseTime();
    total_waiting_time += processes[0].getWaitingTime();
    total_turnaround_time += processes[0].getTurnaroundTime();
    total_return_time += processes[0].getBurst();

    for (size_t i = 1; i < processes.size(); ++i) {
        int waiting_time = max(0, total_return_time - processes[i].getArriveTime());
        processes[i].setWaitingTime(waiting_time);
        processes[i].setReturnTime(total_return_time + processes[i].getBurst());
        processes[i].setTurnaroundTime(processes[i].getReturnTime() - processes[i].getArriveTime());
        processes[i].setResponseTime(processes[i].getWaitingTime());

        total_return_time += processes[i].getBurst();
        total_waiting_time += processes[i].getWaitingTime();
        total_turnaround_time += processes[i].getTurnaroundTime();
        total_response_time += processes[i].getResponseTime();
    }

    cout << "\n\tFCFS Scheduling Algorithm\n\n";

    fcfs_print_gantt_chart(processes);

    cout << "\n\tAverage Waiting Time     : " << fixed << setprecision(2) << static_cast<double>(total_waiting_time) / processes.size() << "\n";
    cout << "\tAverage Turnaround Time  : " << fixed << setprecision(2) << static_cast<double>(total_turnaround_time) / processes.size() << "\n";
    cout << "\tAverage Response Time    : " << fixed << setprecision(2) << static_cast<double>(total_response_time) / processes.size() << "\n\n";

    print_table(processes);
}

#endif
