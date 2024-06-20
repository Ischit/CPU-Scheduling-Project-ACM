#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
using namespace std;

constexpr int ID_LEN = 20;

class Process {
private:
    string id;       
    int arrive_time;      
    int waiting_time;     
    int return_time;      
    int turnaround_time;  
    int response_time;    
    int burst;            
    int priority;         
    bool completed;       

public:
    Process() 
        : id(""), 
          arrive_time(0), 
          waiting_time(0), 
          return_time(0), 
          turnaround_time(0), 
          response_time(0), 
          burst(0), 
          priority(0), 
          completed(false) 
    {}

    string getId() const { return id; }
    int getArriveTime() const { return arrive_time; }
    int getWaitingTime() const { return waiting_time; }
    int getReturnTime() const { return return_time; }
    int getTurnaroundTime() const { return turnaround_time; }
    int getResponseTime() const { return response_time; }
    int getBurst() const { return burst; }
    int getPriority() const { return priority; }
    bool isCompleted() const { return completed; }

    void setId(const string& new_id) { id = new_id; }
    void setArriveTime(int new_arrive_time) { arrive_time = new_arrive_time; }
    void setWaitingTime(int new_waiting_time) { waiting_time = new_waiting_time; }
    void setReturnTime(int new_return_time) { return_time = new_return_time; }
    void setTurnaroundTime(int new_turnaround_time) { turnaround_time = new_turnaround_time; }
    void setResponseTime(int new_response_time) { response_time = new_response_time; }
    void setBurst(int new_burst) { burst = new_burst; }
    void setPriority(int new_priority) { priority = new_priority; }
    void setCompleted(bool new_completed) { completed = new_completed; }
};

using Quantum = int;

void process_init(vector<Process>& p) {
    for (auto &process : p) {
        process.setWaitingTime(0);    
        process.setReturnTime(0);     
        process.setTurnaroundTime(0);
        process.setResponseTime(0);   
        process.setCompleted(false);  
    }
}

#endif
