#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

   struct Process processes[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;
    float totalWT = 0, totalTAT = 0;
    int prev = -1;

    while (completed != n) {
        int idx = -1;
        int minRemaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRemaining) {
                    minRemaining = processes[i].remainingTime;
                    idx = i;
                }
                // Tie-breaker: earlier arrival time
                else if (processes[i].remainingTime == minRemaining && processes[i].arrivalTime < processes[idx].arrivalTime) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].remainingTime--;
            currentTime++;

            // If process finishes
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

                totalWT += processes[idx].waitingTime;
                totalTAT += processes[idx].turnaroundTime;
                completed++;
            }
        } else {
            currentTime++; // CPU is idle
        }
    }

    // Output
    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";
    for (auto &p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime
             << "\t" << p.completionTime << "\t" << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << "\n";

    return 0;
}
