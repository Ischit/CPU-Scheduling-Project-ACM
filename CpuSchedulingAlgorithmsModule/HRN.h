#ifndef HIGHEST_RESPONSE_RATIO_NEXT_H
#define HIGHEST_RESPONSE_RATIO_NEXT_H

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void hrn_print_gantt_chart(const vector<Process>& processes) {
    int len = processes.size();

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

    cout << "\n\t";

    cout << "0";

    for (const auto& process : processes) {
        for (int j = 0; j < process.getBurst(); j++) cout << "  ";
        if (process.getReturnTime() > 9) cout << "\b";
        cout << process.getReturnTime();
    }

    cout << "\n";
}

void HRN(vector<Process> processes) {
    int len = processes.size();
    int time = 0;
    int loc = 0;
    int total_burst_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    float hrr, temp;

    process_init(processes);

    for (const auto& process : processes) total_burst_time += process.getBurst();

    merge_sort_by_arrive_time(processes, 0, len - 1);

    for (time = processes[0].getArriveTime(); time < total_burst_time;) {
        hrr = -9999;

        for (int i = 0; i < len; i++) {
            if ((processes[i].getArriveTime() <= time) && (!processes[i].isCompleted())) {
                temp = (float)(processes[i].getBurst() + (time - processes[i].getArriveTime())) / processes[i].getBurst();

                if (hrr < temp) {
                    hrr = temp;
                    loc = i;
                }
            }
        }

        time += processes[loc].getBurst();

        processes[loc].setWaitingTime(time - processes[loc].getArriveTime() - processes[loc].getBurst());
        processes[loc].setTurnaroundTime(time - processes[loc].getArriveTime());
        processes[loc].setReturnTime(processes[loc].getTurnaroundTime() + processes[loc].getArriveTime());
        processes[loc].setResponseTime(processes[loc].getWaitingTime());
        processes[loc].setCompleted(true);

        total_waiting_time += processes[loc].getWaitingTime();
        total_turnaround_time += processes[loc].getTurnaroundTime();
        total_response_time += processes[loc].getResponseTime();
    }

    quick_sort_by_return_time(processes);

    cout << "\tHighest Response Ratio Next Scheduling Algorithm\n\n";

    hrn_print_gantt_chart(processes);

    cout << "\n\tAverage Waiting Time     : " << fixed << setprecision(2) << (double)total_waiting_time / len << "\n";
    cout << "\tAverage Turnaround Time  : " << fixed << setprecision(2) << (double)total_turnaround_time / len << "\n";
    cout << "\tAverage Response Time    : " << fixed << setprecision(2) << (double)total_response_time / len << "\n\n";

    print_table(processes);
}

#endif
