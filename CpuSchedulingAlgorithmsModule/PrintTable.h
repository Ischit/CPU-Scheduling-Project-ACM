#ifndef PRINT_TABLE_H
#define PRINT_TABLE_H

#include "Process.h"
#include <iostream>
#include <iomanip>
using namespace std;

void print_table(const vector<Process>& p) {
    cout << "\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+" << endl;
    cout << "\t| PID | Burst Time | Arrive Time | Priority | Return Time |  Response Time  | Waiting Time | Turnaround Time |" << endl;
    cout << "\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+" << endl;

    for (const auto& process : p) {
        cout << "\t| " << setw(3) << process.getId() << " | " 
                  << setw(10) << process.getBurst() << " | " 
                  << setw(11) << process.getArriveTime() << " | " 
                  << setw(8) << process.getPriority() << " | " 
                  << setw(11) << process.getReturnTime() << " | " 
                  << setw(15) << process.getResponseTime() << " | " 
                  << setw(12) << process.getWaitingTime() << " | " 
                  << setw(15) << process.getTurnaroundTime() << " |" << endl;
        cout << "\t+-----+------------+-------------+----------+-------------+-----------------+--------------+-----------------+" << endl;
    }

    cout << endl;
}

#endif
