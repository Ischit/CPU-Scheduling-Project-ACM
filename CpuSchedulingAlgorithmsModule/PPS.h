#ifndef PREEMPTIVE_PRIORITY_SCHEDULING_H
#define PREEMPTIVE_PRIORITY_SCHEDULING_H

#include "Process.h"
#include "SortingFunction.h"
#include "PrintTable.h"
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void pps_calculate_time(vector<Process>& processes) {
    int len = processes.size();
    int current_time = 0;
    int total_burst_time = 0;
    int k = 0;

    vector<int> remain_burst_time(len);
    vector<int> count(len, 0);

    for (int i = 0; i < len; i++) {
        remain_burst_time[i] = processes[i].getBurst();
        total_burst_time += processes[i].getBurst();
    }

    while (current_time < total_burst_time) {
        int priority = INT_MAX;

        if (current_time <= processes[len - 1].getArriveTime()) {
            for (int i = 0; i < len; i++) {
                if (!processes[i].isCompleted() && processes[i].getArriveTime() <= current_time && priority > processes[i].getPriority()) {
                    priority = processes[i].getPriority();
                    k = i;
                }
            }
        } 
		else {
            for (int i = 0; i < len; i++) {
                if (!processes[i].isCompleted() && priority > processes[i].getPriority()) {
                    priority = processes[i].getPriority();
                    k = i;
                }
            }
        }

        if (count[k] == 0) {
            count[k]++;
            processes[k].setResponseTime(current_time);
        }

        remain_burst_time[k]--;
        current_time++;

        if (remain_burst_time[k] == 0) {
            processes[k].setCompleted(true);
            processes[k].setWaitingTime(current_time - processes[k].getBurst() - processes[k].getArriveTime());
            processes[k].setReturnTime(current_time);
        }
    }
}

void pps_print_gantt_chart(vector<Process> &p) {
	int i;
    int len = p.size();
	int total_burst_time = 0;
	int current_time = 0, previous_time = 0;
	int k, pre_k = 0;
	int priority, num;

	vector<int> count(len);
	vector<int> remain_burst_time(len);
	for (i = 0; i < len; i++) {
		remain_burst_time[i] = p[i].getBurst();
		total_burst_time += p[i].getBurst();
		p[i].setCompleted(false);
		count[i] = 0;
	}

	cout<<("\t ");

	while (current_time < total_burst_time) {
		priority = INT_MAX;
		if (current_time <= p[len - 1].getArriveTime()) {
			for (i = 0; i < len; i++) {
				if ((p[i].isCompleted() == false) && (p[i].getArriveTime() <= current_time)) {
					if (priority > p[i].getPriority()) {
						priority = p[i].getPriority();
						k = i;
					}
				}
			}
		}

		else {
			for (i = 0; i < len; i++) {
				if (p[i].isCompleted() == false) {
					if (priority > p[i].getPriority()) {
						priority = p[i].getPriority();
						k = i;
					}
				}
			}
		}

		if (pre_k != k) cout<<(" ");

		cout<<("--");
		remain_burst_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_burst_time[k] == 0) p[k].setCompleted(true);
	}

	for (i = 0; i < len; i++) {
		remain_burst_time[i] = p[i].getBurst();
		p[i].setCompleted(false);
	}

	cout<<("\n\t|");
	current_time = 0;

	while (current_time < total_burst_time) {
		priority = INT_MAX;

		if (current_time <= p[len - 1].getArriveTime()) {
			for (i = 0; i < len; i++) {
				if ((p[i].isCompleted() == false) && (p[i].getArriveTime() <= current_time)) {
					if (priority > p[i].getPriority()) {
						priority = p[i].getPriority();
						k = i;
					}
				}
			}
		}

		else {
			for (i = 0; i < len; i++) {
				if (p[i].isCompleted() == false) {
					if (priority > p[i].getPriority()) {
						priority = p[i].getPriority();
						k = i;
					}
				}
			}
		}

		if (current_time == 0) {
			count[k]++;
			cout<<("  ");
		}

		else {
			if (pre_k != k) {
				num = count[pre_k] + 1;
				count[pre_k] = 0;
				count[k]++;
				for (i= 0; i < num; i++) cout<<("\b");
				cout<<(p[pre_k].getId());
				for (i = 0; i < num - 2; i++) cout<<(" ");
				cout<<("|  ");
			}

			else {
				count[k]++;
				cout<<("  ");
				if (current_time == total_burst_time - 1) {
					num = count[pre_k] + 1;
					count[pre_k] = 0;
					count[k]++;
					for (i = 0; i < num; i++) cout<<("\b");
					cout<<(p[pre_k].getId());
					for (i = 0; i < num - 2; i++) cout<<(" ");
				}
			}
		}

		pre_k = k;
		remain_burst_time[k]--;
		current_time++;

		if (remain_burst_time[k] == 0) p[k].setCompleted(true);
	}

	for (i = 0; i < len; i++) {
		remain_burst_time[i] = p[i].getBurst();
		p[i].setCompleted(false);
	}

	cout<<("|\n\t");
	current_time = 0;

	while (current_time < total_burst_time) {
		priority = INT_MAX;

		if (current_time <= p[len - 1].getArriveTime()) {
			for (i = 0; i < len; i++) {
				if ((p[i].isCompleted() == false) && (p[i].getArriveTime() <= current_time)) {
					if (priority > p[i].getPriority()) {
						priority = p[i].getPriority();
						k = i;
					}
				}
			}
		}

		else {
			for (i = 0; i < len; i++) {
				if (p[i].isCompleted() == false) {
					if (priority > p[i].getPriority()) {
						priority = p[i].getPriority();
						k = i;
					}
				}
			}
		}

		if (pre_k != k) cout<<(" ");

		cout<<("--");

		remain_burst_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_burst_time[k] == 0) p[k].setCompleted(true);
	}

	for (i = 0; i < len; i++) {
		remain_burst_time[i] = p[i].getBurst();
		p[i].setCompleted(false);
	}

	current_time = 0;
	num = 0;
	cout<<("\n\t");

	while (current_time <= total_burst_time) {
		if (total_burst_time != current_time) {
			priority = INT_MAX;

			if (current_time <= p[len - 1].getArriveTime()) {
				for (i = 0; i < len; i++) {
					if ((p[i].isCompleted() == false) && (p[i].getArriveTime() <= current_time)) {
						if (priority > p[i].getPriority()) {
							priority = p[i].getPriority();
							k = i;
						}
					}
				}
			}

			else {
				for (i = 0; i < len; i++) {
					if ((p[i].isCompleted() == false) && (priority > p[i].getPriority())) {
						priority = p[i].getPriority();
						k = i;
					}
				}
			}


			if (pre_k != k) {
				for (i = 0; i < num && current_time != 0; i++) cout<<"  ";
				if (current_time != 0) cout<<" ";
				cout<<(current_time)<<" ";
				num = 0;
				previous_time = current_time;
			}

			else num++;
			remain_burst_time[k]--;
			current_time++;
			pre_k = k;
			if (remain_burst_time[k] == 0) p[k].setCompleted(true);
		}

		else {
			for (i = 0; i < current_time - previous_time - 1; i++) cout<<"  ";
			cout<<" ";
			cout<<current_time<<" ";
			break;
		}
	}

	cout<<("\n");
}

void PPS(vector<Process> processes) {
    int len = processes.size();
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    process_init(processes);
    merge_sort_by_arrive_time(processes, 0, len - 1);

    pps_calculate_time(processes);

    for (int i = 0; i < len; i++) {
        processes[i].setTurnaroundTime(processes[i].getReturnTime() - processes[i].getArriveTime());
        total_waiting_time += processes[i].getWaitingTime();
        total_turnaround_time += processes[i].getTurnaroundTime();
        total_response_time += processes[i].getResponseTime();
    }

    cout << "\tPreemptive Priority Scheduling Algorithm\n\n";
    pps_print_gantt_chart(processes);

    cout << "\n\tAverage Waiting Time     : " << fixed << setprecision(2) << (double)total_waiting_time / len << "\n";
    cout << "\tAverage Turnaround Time  : " << fixed << setprecision(2) << (double)total_turnaround_time / len << "\n";
    cout << "\tAverage Response Time    : " << fixed << setprecision(2) << (double)total_response_time / len << "\n\n";

    print_table(processes);
}

#endif
