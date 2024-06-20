#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "Process.h"
#include "SortingFunction.h"
#include "PrintTable.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void rr_calculate_waiting_time(vector<Process>& processes, Quantum q) {
    int curr_time = 0;
    vector<int> remain_burst_time(processes.size());

    for (int i = 0; i < processes.size(); ++i) remain_burst_time[i] = processes[i].getBurst();

    while (true) {
        bool check = true;
        for (int i = 0; i < processes.size(); ++i) {
            if (remain_burst_time[i] > 0) {
                check = false;
                if (remain_burst_time[i] > q) {
                    curr_time += q;
                    remain_burst_time[i] -= q;
                } else {
                    curr_time += remain_burst_time[i];
                    processes[i].setWaitingTime(curr_time - processes[i].getBurst());
                    remain_burst_time[i] = 0;
                }
            }
        }
        if (check) break;
    }
}

void rr_calculate_turnaround_time(vector<Process>& processes) {
    for (auto& process : processes) {
        process.setTurnaroundTime(process.getBurst() + process.getWaitingTime());
    }
}

void rr_print_gantt_chart(vector<Process> &p, Quantum q) {
	int i, j;
    int len = p.size();
	int curr_time = 0, total_burst_time = 0;
	int temp_total_burst_time = 0;

	vector<int> remain_burst_time(len);

	for (i = 0; i < len; i++) {
		remain_burst_time[i] = p[i].getBurst();
		total_burst_time += p[i].getBurst();
	}

	cout<<("\t");

	while (true) {
		int check = true;

		for (i = 0; i < len; i++) {
			if (remain_burst_time[i] > 0) {
				check = false;

				if (remain_burst_time[i] < q) {
					cout<<(" ");
					for (j = 0; j < remain_burst_time[i]; j++) cout<<("--");
				}
				else {
					cout<<(" ");
					for (j = 0; j <= q; j++) cout<<("--");
				}
				if (remain_burst_time[i] > q){
					curr_time += q;
					remain_burst_time[i] -= q;
				}
				else {
					curr_time += remain_burst_time[i];
					p[i].setWaitingTime(curr_time - p[i].getBurst());
					remain_burst_time[i] = 0;
				}
			}
		}
		if (check) break;
	}

	cout<<(" \n\t");

	for (i = 0; i < len; i++) remain_burst_time[i] = p[i].getBurst();

	while (true) {
		int check = true;
		for (i = 0; i < len; i++) {
			if (remain_burst_time[i] > 0) {
				check = false;
				if (remain_burst_time[i] < q) {
					cout<<("|");
					if (remain_burst_time[i] != 1) {
						for (j = 0; j <= remain_burst_time[i] / 2; j++) cout<<(" ");
						cout<<(p[i].getId());
						for (j = 0; j <= remain_burst_time[i] / 2; j++) cout<<(" ");
					}
					else cout<<(p[i].getId());
				}
				else {
					cout<<("|");
					for (j = 0; j < q; j++) cout<<(" ");
					cout<<(p[i].getId());
					for (j = 0; j < q; j++) cout<<(" ");
				}
				if (remain_burst_time[i] > q) {
					curr_time += q;
					remain_burst_time[i] -= q;
				}
				else {
					curr_time += remain_burst_time[i];
					p[i].setWaitingTime(curr_time - p[i].getBurst());
					remain_burst_time[i] = 0;
				}
			}
		}
		if (check == true) break;
	}
	cout<<("|\n\t");
	for (i = 0; i < len; i++) remain_burst_time[i] = p[i].getBurst();

	while (true) {
		int check = true;

		for (i = 0; i < len; i++) {
			if (remain_burst_time[i] > 0) {
				check = false;
				if (remain_burst_time[i] < q) {
					cout<<(" ");
					for (j = 0; j < remain_burst_time[i]; j++) cout<<("--");
				}
				else {
					cout<<(" ");
					for (j = 0; j <= q; j++) cout<<("--");
				}
				if (remain_burst_time[i] > q) {
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else {
					curr_time += remain_burst_time[i];
					p[i].setWaitingTime(curr_time - p[i].getBurst());
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check) break;
	}
	cout<<("\n\t");
	for (i = 0; i < len; i++) remain_burst_time[i] = p[i].getBurst();
	curr_time = 0;
	while (true) {
		int check = true;
		for (i = 0; i < len; i++) {
			if (remain_burst_time[i] > 0) {
				check = false;
				if (remain_burst_time[i] < q) {
					cout<<curr_time;
					for (j = 0; j < remain_burst_time[i] - 1; j++) cout<<("  ");
					cout<<(" ");
				}
				else {
					cout<<(curr_time);
					for (j = 0; j < q; j++) cout<<("  ");
					cout<<(" ");
				}
				if (remain_burst_time[i] > q) {
					curr_time += q;
					remain_burst_time[i] -= q;
				}
				else {
					curr_time += remain_burst_time[i];
					p[i].setWaitingTime(curr_time - p[i].getBurst());
					remain_burst_time[i] = 0;
				}
			}
		}
		if (check == true) break;
	}
	cout<<total_burst_time;
	cout<<("\n");
}

void RR(vector<Process> processes, Quantum quantum) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    process_init(processes);

    merge_sort_by_arrive_time(processes, 0, processes.size()-1);

    rr_calculate_waiting_time(processes, quantum);

    rr_calculate_turnaround_time(processes);

    for (auto& process : processes) {
        process.setWaitingTime(process.getTurnaroundTime() - process.getBurst());
        process.setReturnTime(process.getArriveTime() + process.getBurst() + process.getWaitingTime());

        total_waiting_time += process.getWaitingTime();
        total_turnaround_time += process.getTurnaroundTime();
        total_response_time += process.getResponseTime();
    }
    cout << "\tRound Robin Scheduling Algorithm ( Quantum : " << quantum << " )\n\n";
    rr_print_gantt_chart(processes, quantum);
    cout << "\n\tAverage Waiting Time     : " << fixed << setprecision(2) << (double)total_waiting_time / (double)processes.size() << "\n";
    cout << "\tAverage Turnaround Time  : " << fixed << setprecision(2) << (double)total_turnaround_time / (double)processes.size() << "\n";
    cout << "\tAverage Response Time    : " << fixed << setprecision(2) << (double)total_response_time / (double)processes.size() << "\n\n";
    print_table(processes);
}

#endif
