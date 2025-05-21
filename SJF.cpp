#include <bits/stdc++.h>
using namespace std;
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    bool isCompleted;
};

bool compare(Process a, Process b) {
    if (a.arrivalTime == b.arrivalTime)
        return a.burstTime < b.burstTime;
    return a.arrivalTime < b.arrivalTime;
}

int main() {
	//Non Preemptive  && different arrival time support
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
      struct Process  processes[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].id = i + 1;
        processes[i].isCompleted = false;
    }

    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed != n) {
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            currentTime = processes[idx].completionTime;

            processes[idx].isCompleted = true;
            completed++;

            totalWaitingTime += processes[idx].waitingTime;
            totalTurnaroundTime += processes[idx].turnaroundTime;
        } else {
            currentTime++; 
        }
    }
   for (auto &p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t" << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }  

    cout<<"Average Waiting Time:"<<totalWaitingTime / n;
    cout<<"Average Turnaround Time: " << totalTurnaroundTime / n << "\n";

    return 0;
}
