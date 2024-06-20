#ifndef SHORTEST_JOB_FIRST_H
#define SHORTEST_JOB_FIRST_H

#include "Process.h"
#include "SortingFunction.h"
#include "PrintTable.h"
#include <iostream>
#include <iomanip> 
#include <limits>
using namespace std;

void sjf_calculate_time(vector<Process>& processes) {
    int curr_time = 0;
    size_t len = processes.size();

    processes[0].setCompleted(true);
    processes[0].setReturnTime(processes[0].getArriveTime() + processes[0].getBurst());
    processes[0].setTurnaroundTime(processes[0].getBurst());
    processes[0].setWaitingTime(0);
    curr_time = processes[0].getReturnTime();
    for (size_t i = 1; i < len; ++i) {
        int min_index = -1;
        for (size_t j = 1; j < len; ++j) if (!processes[j].isCompleted() && processes[j].getArriveTime() <= curr_time) if (min_index == -1 || processes[j].getBurst() < processes[min_index].getBurst()) min_index = j;
        if (min_index == -1) {
            for (size_t j = 1; j < len; ++j) {
                if (!processes[j].isCompleted()) {
                    min_index = j;
                    break;
                }
            }
            curr_time = processes[min_index].getArriveTime();
        }

        processes[min_index].setWaitingTime(curr_time - processes[min_index].getArriveTime());
        processes[min_index].setCompleted(true);

        curr_time += processes[min_index].getBurst();

        processes[min_index].setReturnTime(curr_time);
        processes[min_index].setTurnaroundTime(processes[min_index].getReturnTime() - processes[min_index].getArriveTime());
    }
}

void sjf_print_gantt_chart(const vector<Process>& processes) {
    cout << "\t ";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst(); ++j) cout << "--";
        cout << " ";
    }

    cout << "\n\t|";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst() - 1; ++j) cout << " ";
        cout << process.getId();
        for (int j = 0; j < process.getBurst() - 1; ++j) cout << " ";
        cout << "|";
    }

    cout << "\n\t ";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst(); ++j) cout << "--";
        cout << " ";
    }

    cout << "\n\t0";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst(); ++j) cout << "  ";
        if (process.getReturnTime() > 9) cout << "\b";
        cout << process.getReturnTime();
    }

    cout << "\n";
}

void SJF(vector<Process> processes) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    process_init(processes); 
    merge_sort_by_arrive_time(processes, 0, processes.size()-1);

    sjf_calculate_time(processes);

    for (auto& process : processes) {
        process.setResponseTime(process.getWaitingTime());

        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
        total_response_time += process.getResponseTime();
    }

    cout << "\tSJF Scheduling Algorithm\n\n";

    quick_sort_by_return_time(processes);

    sjf_print_gantt_chart(processes);

    cout << "\n\tAverage Waiting Time     : " << fixed << setprecision(2) << (double)total_waiting_time / processes.size() << "\n";
    cout << "\tAverage Turnaround Time  : " << fixed << setprecision(2) << (double)total_turnaround_time / processes.size() << "\n";
    cout << "\tAverage Response Time    : " << fixed << setprecision(2) << (double)total_response_time / processes.size() << "\n\n";

    print_table(processes);
}

#endif
